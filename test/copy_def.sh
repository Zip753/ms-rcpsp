#!/bin/bash

for def_name in `ls def/*.def`
do
	def_name=`basename $def_name`
	name=${def_name%.def}

	echo $name
	cp "def/$def_name" "res/$name/"
done
