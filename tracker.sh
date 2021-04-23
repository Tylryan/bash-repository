#!/usr/bin/bash

subject=$1
date=$2
hours=$3
if [ ! -z ${subject} ] && [ ! -z ${date} ] && [ ! -z ${hours} ]
	then
		echo "${subject},${date},${hours}" >> $(find ~/Documents -iname records.csv)
else 
	echo "You need to have a Subject Date and Hours in that order."
fi
