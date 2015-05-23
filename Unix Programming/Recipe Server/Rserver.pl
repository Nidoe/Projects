#!/usr/bin/perl

#*******************************#
#Name: Luv Somani               #
#Student Number:14024639        #
#Pawprint: lrsfh3               #
#CS3530 Homework #3-Server      #
#*******************************#

use IO::Socket;
use Switch;
my $port;

#Read in Arguments

if(($#ARGV + 1) eq 2){
	$port = "$ARGV[0]";
}
else{
	print "Invalid Server Execution\n";
	print "Format: ./Rserver.pl <port> <Recipe file>\n";
	exit;
}
#Open Recipe File
open(RECIPE, $ARGV[1]) or die "cannot open $ARGV[1]";

#Declare Variables
my @RecipeNames;
my @RecipeIngredients;
my @RecipeInstructions;
my $count = 0;
my $parseingredients;
my $parseinstructions;

#Parse Recipe into Arrays
while($line = <RECIPE>){
	if($parseingredients eq 1){
		if($line ne "<\/ingredients>\n"){
		@RecipeIngredients[$count] = @RecipeIngredients[$count] . $line;
		}
	}

	if($parseinstructions eq 1){
		if($line ne "<\/instructions>\n"){
		@RecipeInstructions[$count] = @RecipeInstructions[$count] . $line;
		}
	}
	switch ($line) {
		case /Recipe name=/{
			my $temp = substr $line,14;
			@RecipeNames[$count] = substr $temp,0,-3;
			@RecipeNames[$count] = @RecipeNames[$count] . "\n";
		}
		case /<ingrdients>/{
			$parseingredients = 1;
		}
		case /<\/ingredients>/{
			$parseingredients = 0;
		}
		case /<instructions>/{
			$parseinstructions = 1;
		}
		case /<\/instructions>/{
			$parseinstructions = 0;
		}
		case /Recipe>/{
			$count = $count + 1;
		}
	}
}

#Open Socket
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
while ($addr = $local->accept() ) {	# receive a request
	print 	"Connected from: ", $addr->peerhost();	# Display messages
	print	" Port: ", $addr->peerport(), "\n";
	#Recipe List Function
	print $addr $count . "\n";
	sub RecipeList{
		for($i = 0; $i < $count; $i++){
			my $temp = $i + 1;
			print $addr $temp . ") " . @RecipeNames[$i];	
		}	
	}
	&RecipeList;
	#Get Recipe Function
	sub GetRecipe{
		my $RecipeReq = <$addr>;
		chomp;
		$RecipeReq = $RecipeReq - 1;
		if($RecipeReq lt $count){
			print $addr "Success" . "\n";
			print $addr "Recipe: " . $RecipeNames[$RecipeReq];
			print $addr "Ingredients:\n" . $RecipeIngredients[$RecipeReq];
			print $addr "Instructions:\n" . $RecipeInstructions[$RecipeReq];
			print $addr "Done\n";
			&RecipeList;		
		}
	}
	&GetRecipe;
	

		
	}
#	else { print "Skipping Send Response : $_ \n"; }

	print "Closed connection\n";	# Inform that connection 
	# to client is closed
	close $addr;	# close client
	print "At your service. Waiting...\n";	# Wait again for next request
	#Close File
	close(RECIPE);
