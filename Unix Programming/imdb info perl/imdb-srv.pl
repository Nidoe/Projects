#!/usr/bin/perl
#*******************************#
#Name: Luv Somani		#
#Student Number:14024639	#
#Pawprint: lrsfh3		#
#CS3530 Project #2-Server	#
#*******************************#

use IO::Socket;
use IMDB::Film;
use IMDB::Persons;
use Text::Table;

$port = 2076;
$hostname=`hostname`;
$local = IO::Socket::INET->new(
		Proto	 => 'tcp',		# protocol
		LocalPort => $port,	# Host and port to listen to
 # Change the port if 8081 is being used
		Reuse => 1,
		Listen => 1
		) or die "$!";
$local->listen();	# listen
$local->autoflush(1);	
		# To send response immediately
	print "At your service. Waiting on $hostname at port $port ...\n";
my $addr;	# Client handle

while($addr = $local->accept() ){

	print 	"Connected from: ", $addr->peerhost();	# Display messages
	print	" Port: ", $addr->peerport(), "\n";
	
	#Person Search Subroutine
	sub PersonSearch{
		#Get person name as argument
		my $person = shift;
		#Create IMDBPerson object
		my $IMDBPerson = new IMDB::Persons(crit=>$person);
		#If valid person
		if($IMDBPerson->status){
			#Send found message to client
                        print $addr "Found" . "\n";
			#Create table of values
			my $PersonTable = new Text::Table(("Name","Birth Date","Place of birth"));
		        $PersonTable->add("------------","-------------","---------------------");
			#Add values to table
			$PersonTable->add($IMDBPerson->name,$IMDBPerson->date_of_birth, $IMDBPerson->place_of_birth);
			#Send table to client
			my @table = $PersonTable->table;
			print $addr @table;
		}
		#Error message
		else{
			print $addr "Not Found" . "\n";
			}
		}
	
	#Film Search Subroutine
	sub FilmSearch{
		#Get film name as argument
		my $film = shift;
		#Create IMDBFilm object
		my $IMDBFilm = new IMDB::Film(crit=>$film);
		#If valid film
		if($IMDBFilm->status){
			#Send found message to client
			print $addr "Found" . "\n";
		   	#Release Date objects
			my $releasedate = $IMDBFilm->release_dates();
			#Create table
			my $MovieTable = new Text::Table(("Title","Runtime","Year","Release Date"));
		        $MovieTable->add("-----------","--------","-----","-----------------");
			#Add values to table
			$MovieTable->add($IMDBFilm->title(),$IMDBFilm->duration(),$IMDBFilm->year(),@$releasedate[0]->{date});
			#Send table to client
			my @table = $MovieTable->table;
			print $addr @table;
		}
		#Error message
		else{
			print $addr "Not Found" . "\n";
			}
		}
	#Read in input from client
	my $inputs = <$addr>;
	chomp;
	#Create substrings to split input
	my $type = substr $inputs,0,1;
	my $input = substr $inputs,2;
	#Check for type of input(Person or Film)
	#If search type is person
	if($type eq "P"){
		#Call Person Subroutine
		&PersonSearch($input);
		}
	#If search type is title
	elsif($type eq "T"){
		#Call Film Subroutine
		&FilmSearch($input);
		}
	#All other requests
	else{
		print $addr "Invalid Request" . "\n";
		}
	close $addr;	# close client
	print "At your service. Waiting...\n";	# Wait again for next request
}
