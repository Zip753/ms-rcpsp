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

	if [ -d "res/$name" ]
	then
		rm -rf "res/$name"
	fi
	mkdir "res/$name"

	for i in {0..9}
	do
		echo "####"
		echo "# Dataset $name, take $i"
		echo "####"

		if [[ $name == 200* ]]
		then
			./$exec "ndef/$name" 50 50
		else
			./$exec "ndef/$name"
		fi
		mv "ndef/$name.sol"  "res/$name/$name.$i.sol"
		mv "ndef/$name.stat" "res/$name/$name.$i.stat"
	done
done
