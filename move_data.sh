#!/bin/bash

for f in *.def *.ndef *.stat *.sol
do
	name=${f%%.*}
	if [ ! -d data/$name ]
	then
		mkdir data/$name
	fi
	mv $f data/$name/$f
done
