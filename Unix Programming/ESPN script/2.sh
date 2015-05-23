#!/bin/bash

#Read input

webaddress='http://www.espn.co.uk/football/sport/video_audio/index.html?keywords=espn+FC+Press+Pass'
curl $webaddress > contents

grep 'ESPN FC Press Pass:' contents | cut -d'>' -f3 | cut -d'<' -f1 > episodes


grep -B 5 'ESPN FC Press Pass:' contents | grep '<img src' | cut -d'/' -f9 | cut -d'.' -f1 > list
count=$(expr 0)
while read line
do
	count=$(expr $count + 1)
	latestep=$(sed -n -e "$count p" episodes)
	smiladdress='http://api.multicastmedia.com/ws/get_smilv2/od/rtmp/here.smil'

	latest=$line
	smiladd=${smiladdress/%here.*/$latest.smil}

	curl $smiladd > smil

	grep '2128K.mp4' smil > u_r_l

	final=$(cut -d'"' -f2 u_r_l | cut -c11-)

	multicasturl="http://espn.multicastmedia.com$final"

	echo $latestep : $multicasturl
done < list
#mv address .bcache/address

#mv .bcache/log log
#mv log .bcache/log

