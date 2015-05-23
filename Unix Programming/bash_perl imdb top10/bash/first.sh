#!/bin/bash

#Get page with top 10 movies
wget http://www.imdb.com/chart/
#Find titles of movies and create a file with the URLs
grep -o '"/title/.*/\"' < index.html | tr -d '"' | head > titles
#Create array for titles
declare -a titlelist
#Read in URLs of the top 10 movies
titlelist=($(< titles)) 

echo "                                  #################################                         "
echo "                                  ########The Top 10 Movies########                         "
echo "                                  #################################                         "
echo "                                                                                                        "
echo "                                                                                                        "
#Add header text to file that will contain all data
echo "Title,Year,Release Date,Runtime," > table
echo "---------------------------------------------------,----,-----------------------,-------" >> table

#Loop through for each URL
for i in `seq 0 9`;
        do
		#Send title to temporary file movies
		curl -s http://www.imdb.com${titlelist[$i]} > movieurl
		cat movieurl | grep '<title>' | cut -d'>' -f2 | cut -d'<' -f1 | cut -d'(' -f1 > movies 
		#Append Year
		cat movieurl | grep '<title>' | cut -d'>' -f2 | cut -d'<' -f1 | cut -d'(' -f2 | cut -d')' -f1 >> movies
		#Append Release Date
		cat movieurl | grep '[0-9]\{2\} [A-Z][a-z]\{2,8\} [0-9]\{4\}' | head -1 >> movies
		#Append Runtime
		cat movieurl | grep -ow '[0-9]\{2,3\} min' | head -1 >> movies
		#Read in temporary file and send all data on same line in table file separated by a comma
		while read line; do
  			echo -ne "${line}," >> table
		done < movies
		#Newline
		echo "" >> table
	done
#Make a table with our file that contains all text
column -ts, -c 250 table
#Remove temporary files
rm index.htm*
rm titles
rm movies
