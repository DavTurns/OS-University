#!/bin/bash

if [ $# -gt 0 ]
then
for ordner in $@
	do
	if [[ -d $ordner ]]
		then
		for datei in `ls $ordner`
		do
		grep -l "[^a-zA-Z]" "$ordner""$datei" | xargs basename
		done
	else echo $ordner" gibt es nicht"
	fi
done
else echo "Keine Parameter angegeben"
fi
