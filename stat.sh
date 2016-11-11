#!/bin/bash

defset='dataset_def'

if [ "$1" = "--config" ]
then
  defset='config_def'
  shift
fi

mode='default'

if [ "$1" == "--one" ]
then
  mode='one'
  shift
elif [ "$1" == "--two" ]
then
  mode='two'
  shift
fi

for def_file in $defset/*.def
do
  name=${def_file%%.*}
  name=${name##*/}
  case $mode in
    one|two)
      echo -n "$(sed 's/_/\\_/g' <<< $name)"
      ;;
    *)
      echo -n $name
      ;;
  esac
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
    mean=`bc -l <<< "scale=2; $mean/$cnt" | sed 's/^\./0./'`

    std=0
    for b in data/$name/$config/*.best
    do
      n=`cat $b`
      std=`bc -l <<< "$std+($n-$mean)*($n-$mean)"`
    done

    std=`bc -l <<< "scale=2; sqrt($std/$cnt)" | sed 's/^\./0./'`

    case $mode in
      one)
        echo -n -e "!& \\\textbf{$mean} \$\\pm\$ $std ($min)"
        ;;
      two)
        echo -n -e "!& $min & $mean & $std"
        ;;
      *)
        echo -n -e "!$min!$mean!$std"
        ;;
    esac
  done
  case $mode in
    one|two)
      echo ' \\ \hline'
      ;;
    *)
      echo
      ;;
  esac
done | column -t -s'!'
