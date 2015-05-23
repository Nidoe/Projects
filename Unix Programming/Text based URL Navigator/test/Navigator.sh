#!/bin/bash
#Name: Luv Somani
#Student Number: 14024639
#Pawprint: lrsfh3
#CS3530 HW#2
mkdir .bcache

declare -a URLList

#Check Arguments
if [ $@ > 0 ]
then
webaddress=$1
else
echo 'Usage : Navigator <url>'
fi

#Set while loop condition to 1(on)
looping='1'
#While loop
while [ "$looping" -eq "1" ]
do
	#Get file for web address
	curl -s $webaddress > address
	#Grab all URLs from web address
	grep -i "http:" address | sed 's/^.*http/http/' | cut -d'"' -f1 > urls
	#Create array of all valid URLs
	URLList=($(<urls))
	count=${#URLList[@]}
	#Move files to .bcache and add webaddress to log
	mv address .bcache
	mv .bcache/log log
	echo $webaddress >> log
	mv log .bcache
	mv urls .bcache	
	#Add Exit condition to final array entry
	URLList[$count]="Enter $count or q to quit"
	#Output all URLs to screen
	for i in `seq 0 $count`;
		do
			echo -ne "$i) "
			echo ${URLList[$i]}
		done
	#Read user choice
	echo "Enter a choice(0-$count): "
	read choice
	#Compare choice to possible matches
	if [ "$choice" -lt "$count" ]
	then
	#Set new web address if valid
	webaddress=${URLList[$choice]}
	else
	#Set loop condition to 0(off)
	looping=0
	fi

done
		

