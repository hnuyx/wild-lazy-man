#!/bin/bash

files=`ls *.cpp`

for file in $files
do
	d2x_str="dos2unix $file"
	echo $d2x_str
	eval $d2x_str
	conv_str="iconv -f gbk $file -o tmpfile"
	echo $conv_str
	eval $conv_str
	if [ $? -eq 0 ]; then
		mv tmpfile $file
	else
		rm tmpfile
	fi
done
