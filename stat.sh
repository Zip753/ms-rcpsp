#!/bin/bash

defset='dataset_def'

if [ "$1" = "--config" ]
then
  defset='config_def'
  shift
fi

for def_file in $defset/*.def
do
  name=${def_file%%.*}
  name=${name##*/}
  echo -n "$name"
  for config in "$@"
  do
    min=123123
    mean=0
    cnt=0
    for b in data/$name/$config/*.best
    do
      n=`cat $b`
      ((n < min)) && min=$n
      ((n > max)) && max=$n
      mean=$(($mean+$n))
      cnt=$(($cnt+1))
    done
    mean=`bc -l <<< "scale=2; $mean/$cnt"`

    std=0
    for b in data/$name/$config/*.best
    do
      n=`cat $b`
      std=`bc -l <<< "$std+($n-$mean)*($n-$mean)"`
    done

    std=`bc -l <<< "scale=2; sqrt($std/$cnt)"`
    echo -n -e "\t$min\t$mean\t$std"
  done
  echo
done | column -t -s"\t"
