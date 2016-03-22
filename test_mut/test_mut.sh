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

	for mut in 0.01 0.02 0.03 0.05 0.1
	do
		res_dir="res/$mut"
		if [ -d $res_dir ]
		then
			rm -rf $res_dir
		fi
		mkdir $res_dir

		for i in {0..9}
		do
			echo "####"
			echo "# Mutation $mut, take $i"
			echo "####"

			./$exec "ndef/$name" 100 100 0.7 $mut

			mv "ndef/$name.sol"  "$res_dir/$name.$i.sol"
			mv "ndef/$name.stat" "$res_dir/$name.$i.stat"
		done
	done
done
