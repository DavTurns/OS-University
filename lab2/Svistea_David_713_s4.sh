#!/bin/bash

wort=$1
datei=$2

if [ $# -eq 2 ]
then
if [[ -e $datei ]]
then
sed -E "s/([a-z])/$wort\1/g" $datei
else echo "Datei nicht gefunden"
fi
else echo "Falsche Anzahl an Parameter"
fi
