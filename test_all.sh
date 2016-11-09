#!/bin/bash

exec='bazel-bin/ga_bin'
defset='dataset_def'

config="$1"
shift
num_tests="$1"
shift

if [ "$1" == "--config" ]
then
  defset='config_def'
  shift
fi

if [ ! -f $exec ]
then
  echo "Please build :ga_bin target with Bazel first."
  exit 1
fi

if [ ! -d 'data' ]
then
  mkdir 'data'
fi

for def_file in $defset/*.def
do
  name=${def_file%%.*}
  name=${name##*/}
  echo "Test sample: $name"
  if [ ! -d "data/$name" ]
  then
    mkdir "data/$name"
  fi
  
  if [ -d "data/$name/$config" ]
  then
    rm -rf "data/$name/$config"
  fi
  mkdir "data/$name/$config"

  for i in $(seq 1 4 $num_tests)
  do
    for j in $(seq $i $(($i+3)) )
    do
      if [ $j -le $num_tests ]
      then
        $exec "$def_file" "data/$name/$config/" "$j" $@ 1>/dev/null &
        echo "$name: $j"
      fi
    done
    wait

    for j in $(seq $i $(($i+3)) )
    do
      if [ $j -le $num_tests ]
      then
        echo "$name: $j BEST $(cat data/$name/$config/$name.$j.best)"
      fi
    done
  done
done
