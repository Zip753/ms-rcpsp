#!/bin/bash

if [ ! -d best ]
then
	mkdir best
fi

if [ -d best/$1 ]
then
	rm -rf best/$1
fi
mkdir best/$1

for f in dataset_def/*.def
do
	name=${f%%.*}
	name=${name##*/}
	min=123123
	for b in data/$name/$1/*.best
	do
		n=`cat $b`
		((n < min)) && min=$n && mini=${b%.*} && mini=${mini#*.}
	done
	echo $min > best/$1/$name.best
	cp data/$name/$1/$name.$mini.sol best/$1/$name.sol
done
