#!/bin/bash

#Read input

webaddress=$1

curl $webaddress > address

grep 'a href="http' address | cut -d'"' -f2 | grep 'http' > list

count=$(wc -l list)

echo $count

#mv address .bcache/address

#mv .bcache/log log
echo $webaddress >> log
#mv log .bcache/log

