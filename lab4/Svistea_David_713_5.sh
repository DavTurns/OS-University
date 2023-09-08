#!/bin/bash

if [ $# -eq 2 ] && [ -d $1 ] && [ -d $2 ] && ! [ -d $1/$2 ]
	then
	for filepath in `find $2 -type f`
		do
		mv $filepath $filepath".eins"
	done
	#mkdir $1/$2
	mv $2/* $1
	#rmdir $2
else
	echo "Error - falsche Parameter eingegeben"
fi
