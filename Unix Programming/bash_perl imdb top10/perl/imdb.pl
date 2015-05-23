#!/usr/bin/perl
#################################
#Name: Luv Somani		#
#Student Number: 14024639	#
#Pawprint: lrsfh3		#
#Project 1a - CS3530		#
#################################

use strict;
use WWW::Mechanize;
use WWW::Mechanize::Link;
use IMDB::Film;
use Text::Table;
print "IMDB Film Search" . "\n";
print "1)Display Current Top10 Movies" . "\n";
print "2)Lookup movie by title" . "\n";
print "Enter a choice: ";
my $choice = <STDIN>;
chomp($choice);
if($choice eq '1'){
	my $movieurl;
	my $movielist = WWW::Mechanize::Link->new();
	my $mech = WWW::Mechanize->new();
	my $url = "http://www.imdb.com/chart/";
	my $tb = new Text::Table(("Title","Runtime","Year","Release Date"));
	$tb->add("-----------","--------","-----","-----------------");
	$mech->agent_alias('Windows IE 6');
	$mech->get($url);
	my @movielist = $mech->find_all_links(url_regex=>qr/title\/tt/);
	splice(@movielist,10);
	foreach(@movielist){
		$movieurl = $_->url;
		&moviedata($movieurl);
		}
	#subroutine to process each url
	sub moviedata{
		my $code;
		foreach(@_){
		$code = substr $_,9,7;
		}
		my $movie = new IMDB::Film(crit => $code);
		my $title = $movie->title();
		my $runtime = $movie->duration();
		my $year = $movie->year();
		my $releasedate = $movie->release_dates();
		my $release = @$releasedate[0]->{date};
		$tb->add($title,$runtime,$year,$release);
	}
	my @lines = $tb->table;
	print @lines;
}
if($choice eq '2'){
	print "Enter a movie name: ";
	my $name = <STDIN>;
	chomp($name);
	my $film = new IMDB::Film(crit => $name);
	my $duration = $film->duration;
	my $releases = $film->release_dates();
	my $release = @$releases[0]->{date};
	print "Title: " . $film->title() . "\n" . "Runtime: " . $duration . "\n" . "Year: " . $film->year() . "\n" . "Release Date: " . $release . "\n";
}
