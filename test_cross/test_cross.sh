#!/bin/bash

if [ -d 'ndef' ]
then
	rm -rf 'ndef'
fi
mkdir 'ndef'

if [ ! -d 'res' ]
then
	mkdir 'res'
fi

if [ -d '../bin/Debug' ]
then
	exec='../bin/Debug/MS-RCPSP'
else
	exec='../bin/Release/MS-RCPSP'
fi

for def_name in `ls def/*.def`
do
	def_name=`basename $def_name`
#	echo $def_name
	name=${def_name%.def}
	echo $name
	
	ruby parse_better.rb "def/$def_name" > /dev/null
	mv "def/$name.ndef" 'ndef'

	for cross in 0.8 0.7 0.6 0.5 0.3
	do
		res_dir="res/$cross"
		if [ -d $res_dir ]
		then
			rm -rf $res_dir
		fi
		mkdir $res_dir

		for i in {0..9}
		do
			echo "####"
			echo "# Crossover $cross, take $i"
			echo "####"

			./$exec "ndef/$name" 100 100 $cross 0.03

			mv "ndef/$name.sol"  "$res_dir/$name.$i.sol"
			mv "ndef/$name.stat" "$res_dir/$name.$i.stat"
		done
	done
done