#!/bin/bash

exec='bin/Debug/MS_RCPSP'

echo $*
#echo $exec
#./$exec 100_20_46_15 100 100 0.4 0.02
#exit 0

if [ ! -d data ]
then
	mkdir data
fi

for f in dataset_def/*.def
do
	name=${f%%.*}
	name=${name##*/}
	echo $name
	if [ ! -d data/$name ]
	then
		mkdir data/$name
	fi
	if [ ! -f data/$name/$name.def ]
	then
		cp $f data/$name
	fi
	if [ ! -f data/$name/$name.ndef ]
	then
		ruby parse_better.rb data/$name/$name.def 1>/dev/null
	fi
	
	if [ -d data/$name/$1 ]
	then
		rm -rf data/$name/$1
	fi
	mkdir data/$name/$1
	for i in $(seq 1 $2)
	do
		./$exec $name $3 $4 $5 $6
		mv data/$name/$name.sol data/$name/$1/$name.$i.sol
		mv data/$name/$name.best data/$name/$1/$name.$i.best
	done
done
