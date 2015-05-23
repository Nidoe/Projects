<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="en" xml:lang="en">
<head>
<title>Luv Somani | CS3380</title><meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
<style type="text/css" media="all">

body {
	font-family: arial, helvetica, sans-serif;
}

h1 {
	font-size: 30;
	text-align:center;
}

h4{
	text-align:center;
}

table#users {
	border: 1px solid black;
	border-collapse: collapse;
	margin-left:auto;
	margin-right:auto;
}

table#users th, td {
	border: 2px solid black;
	padding: 5px;
}


table#users th {
	background-color: #ccccff;
}

table#users td{
	background-color: green;
}

table#users td.subh{
	background-color: #ccccff;
	font-weight: bold;
	text-align: right;
}

table#users tr.heading {
	background-color: #ccffcc;
	color: white;
	font-style:italic;
}

table#users td.data {
	background-color: green;
	vertical-align: top;
	padding: 0px;
}

table#users th.titles {
	background-color: #ccccff;
	font-weight: bold;
	font-size: 20px;
}


</style>
</head>
<body>
<?php
	if($_POST['word'] != NULL){
		$sha1value = sha1($_POST['word']);
		$md5value = md5($_POST['word']);
	}
	
	echo '<h1>Homework 1</h1>
	<table id="users">
		<tr><th class="titles" colspan="3">LUV SOMANI</th></tr>
		<tr class="heading"><th>Links to References/APIs</th><th colspan="2">Personal Information</th></tr>
		<tr>
			<td class="data" rowspan="6">
			<ol>
				<li><a href="http://www.w3schools.com/html/default.asp" target="_blank">HTML</a></li>
				<li><a href="http://www.w3schools.com/php/default.asp" target="_blank">PHP</a></li>
				<li><a href="http://www.danielgibbs.net/journal/md5-and-sha1-decrypting-with-php-mysql" target="_blank">MD5/SHA1</a></li>
			</ol>
			<tr><td class="subh">Pawprint:</td><td>lrsfh3</td></tr>
			<tr><td class="subh">Academic Level:</td><td>Undergrad</td></tr>
			<tr><td class="subh">Major:</td><td>Computer Science</td></tr>
			<tr><td class="subh">Graduation Date:</td><td>May 2012</td></tr>
			<tr><td class="subh">Hash Word:</td><td><form action="Homework1.php" method="POST"><input type="text" name="word"><input type="submit" value="Submit"></td>
			</td>
		</tr>
	</table>';
	if($sha1value != NULL){
	echo '<h4>md5:' . $md5value . '</h4>';
	}
	if($md5value != NULL){
	echo '<h4>sha1:' . $sha1value . '</h4>';
	}
?>
</body>
</html>

