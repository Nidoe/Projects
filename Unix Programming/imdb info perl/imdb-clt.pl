#!/usr/bin/perl

#*******************************#
#Name: Luv Somani               #
#Student Number:14024639        #
#Pawprint: lrsfh3               #
#CS3530 Project #2-Client       #
#*******************************#



use IO::Socket;
use Text::Table;

$rhost = "127.0.0.1";
$port = 2076;

#Loop forever
$loop = 1;
while($loop ne 0){
	$remote = IO::Socket::INET->new(
		Proto	=>'tcp',	# protocol
		PeerAddr=>$rhost,	# Address of server
		PeerPort=>$port,	# port of server
		Reuse => 1,
		) or die "$!";
	print "Connected to ", $remote->peerhost, # Info message
	 " on port: ", $remote->peerport, "\n";
	
	#Input message
	print "**********IMDB Lookup**********\n"; 
	print "Enter P:<person> or T:<Movie title>\n";
	my $input = <STDIN>;	# Get input from STDIN
	print $remote $input; 
	
	#Read in found/invalid/not found
	my $line = <$remote>;
	chomp;
	#If server sends not found
	if($line =~ m/^Not Found/){
		print "Request not found\n";
	#If server sends found
	}elsif($line =~ m/^Found/){
		#Read in all values of table in array
		my @table = <$remote>;
		#Output all data
		print @table;
	}
	#Invalid request
	elsif($line =~ m/^Invalid Request/){
		print "Invalid Request\n";
	}

	close $remote;			# Close socket
}
