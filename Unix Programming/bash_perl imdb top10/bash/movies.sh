#/bin/bash

echo "IMDB Movie Search"
echo "1. Search by name"
echo "2. List of Top 10 Movies"
echo -n "Enter your choice: "
read choiceValue

if(($choiceValue -eq $2)); then
wget http://www.imdb.com/chart/

grep -o '"/title/.*/\"' < index.html | tr -d '"' | head > titles

declare -a titlelist

titlelist=($(< titles)) 
echo "                                  #################################                         "
echo "                                  ########The Top 10 Movies########                         "
echo "                                  #################################                         "
echo "                                                                                                        "
echo "                                                                                                        "
echo "Title,Year,Release Date,Runtime," > table
echo "---------------------------------------------------,----,-----------------------,-------" >> table

for i in `seq 0 9`;
        do
		curl -s http://www.imdb.com${titlelist[$i]} | grep '<title>' | cut -d'>' -f2 | cut -d'<' -f1 | cut -d'(' -f1 > movies 
		curl -s http://www.imdb.com${titlelist[$i]} | grep '<title>' | cut -d'>' -f2 | cut -d'<' -f1 | cut -d'(' -f2 | cut -d')' -f1 >> movies
		curl -s http://www.imdb.com${titlelist[$i]} | grep '[0-9]\{1,2\} [A-Z][a-z]\{2,8\} [0-9]\{4\}' | head -1 >> movies
		curl -s http://www.imdb.com${titlelist[$i]} | grep -ow '[0-9]\{2,3\} min' | head -1 >> movies
		while read line; do
  			echo -ne "${line}," >> table
		done < movies
		echo "" >> table
	done
	column -ts, -c 250 table
fi

rm index.htm*
rm titles
rm movies
