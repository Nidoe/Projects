#!/bin/bash

#Read input

webaddress='www.espn.co.uk/football/sport/video_audio/index.html?genre=6;sport=3'

curl $webaddress > contents

grep 'ESPN FC Press Pass:' contents | cut -d'>' -f3 | cut -d'<' -f1 > episodes


grep -B 5 'ESPN FC Press Pass:' contents | grep '<img src' | cut -d'/' -f9 | cut -d'.' -f1 > list
latest=$(head -1 list)
latestep=$(head -1 episodes)
smiladdress='http://api.multicastmedia.com/ws/get_smilv2/od/rtmp/here.smil'

smiladd=${smiladdress/%here.*/$latest.smil}

curl $smiladd > smil

grep '2128K.mp4' smil > u_r_l

final=$(cut -d'"' -f2 u_r_l | cut -c11-)

multicasturl="http://espn.multicastmedia.com$final"

echo $latestep : $multicasturl

#mv address .bcache/address

#mv .bcache/log log
#mv log .bcache/log

