#!/bin/bash
anzahl_ordner=$1;
anzahl_dateien=$2;
if [ $# -ne 2 ]
	then
	echo "Error - falsche anzahl an Parametern"
	exit 1
	fi
rm -r output
mkdir output
cd output
for (( i = 0; $i<$anzahl_ordner; i++ ))
	do
	
	mkdir $i
	cd $i
	for (( j = 0; $j<$anzahl_dateien; j++ ))
		do
		touch $j
	done
	cd ..	
done
cd ..

	
