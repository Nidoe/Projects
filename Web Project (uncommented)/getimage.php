<?php
require_once('functions.php');

$q=$_GET["q"];

$conn = dbconn();

$query = "SELECT hero_img FROM dota2.heroes WHERE hero_name=$1";

pg_prepare($conn,"GetImage",$query);

$img = pg_execute($conn,"GetImage", array($q));

while($row = pg_fetch_assoc($img)){
	$image_url = $row['hero_img'];
	
	print "<img src=\"images/heroes/$image_url.png\" alt=\"$q image \"></img>";
}




?>

