#!/bin/bash

if [ $# -lt 1 ]
	then
	echo "Error - keine Parameter"
	exit 1
fi
for datei in $@
	do
	if [ -f $datei ]
		then
		awk '{for (i=1; i<=length($0); i++) {
    			char = toupper(substr($0, i, 1))
			if (match(char, /[AEIOU]/)) {
      				vokale += 1
			}
			if (match(char, /[BCDFGHJKLMNPQRSTVWXYZ]/)) {
				konsonanten += 1
			}
			}} END {print FILENAME " - Vokale: " vokale " Konsonanten: " konsonanten}' $datei
	else
		echo $datei "gibt es nicht"
	fi
done
