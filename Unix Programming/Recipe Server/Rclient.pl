#!/usr/bin/perl

#*******************************#
#Name: Luv Somani               #
#Student Number:14024639        #
#Pawprint: lrsfh3               #
#CS3530 Homework #3-Client      #
#*******************************#


use IO::Socket;

#Read in Arguments
if(($#ARGV + 1) eq 2){
	$rhost = "$ARGV[0]";
	$port = $ARGV[1];
}
else{
        print "Invalid Client Execution\n";
        print "Format: ./Rclient.pl <host> <port>\n";
        exit;
}

#Loop Forever
my $looping = 1;
while($looping ne 0){
$remote = IO::Socket::INET->new(
		Proto	=>'tcp',	# protocol
		PeerAddr=>$rhost,	# Address of server
		PeerPort=>$port,	# port of server
		Reuse => 1,
		) or die "$!";
print "Connected to ", $remote->peerhost, # Info message
 " on port: ", $remote->peerport, "\n";

	#Recieve Server Information
	my $count = <$remote>;

	#Recipe List
	for($i = 0; $i < $count; $i++){
		my $res = <$remote>;
		print $res;
	}
	my $input = <STDIN>;

	#Request Recipe
	print $remote $input;
	my $line = <$remote>;
	chomp;
	if($line =~ m/^Success/){
		while($line = <$remote>){
		if($line eq "Done\n"){
			last;
			}
		elsif($line ne "Done\n"){
			print $line;
			}
		}
	}
	#End Current Loop, Request list Again

	print "Requesting List...\n";	# End of client
	close $remote;			# Close socket

}
