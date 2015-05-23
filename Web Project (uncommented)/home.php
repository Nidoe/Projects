<?php
	require_once('functions.php');
	$conn = dbconn();
	session_start();
	if(isset($_SESSION['loggedin'])){
		$currenthero = $_SESSION['fav_hero'];
	}
	else{
		header('Location:login.php');
	}
	if(isset($_GET['hero'])){
		$currenthero = $_GET['hero'];
	}
?>
<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8" />

  	<meta name="viewport" content="width=device-width" />

	<title>Dota 2 Dashboard</title>
  
  	<link rel="stylesheet" href="stylesheets/foundation.css">
	<link rel="stylesheet" href="stylesheets/foundation.min.css">
	<link rel="stylesheet" href="stylesheets/app.css">
	
	<script src="javascripts/twitch.js"></script>
	<script src="javascripts/modernizr.foundation.js"></script>
	<script src="javascripts/jquery.js"></script>
	<script src="javascripts/jquery.foundation.mediaQueryToggle.js"></script>
	<script src="javascripts/jquery.foundation.forms.js"></script>
	<script src="javascripts/jquery.foundation.reveal.js"></script>
	<script src="javascripts/jquery.foundation.orbit.js"></script>
	<script src="javascripts/jquery.foundation.navigation.js"></script>
	<script src="javascripts/jquery.foundation.buttons.js"></script>
	<script src="javascripts/jquery.foundation.tabs.js"></script>
	<script src="javascripts/jquery.foundation.tooltips.js"></script>
	<script src="javascripts/jquery.foundation.accordion.js"></script>
	<script src="javascripts/jquery.placeholder.js"></script>
	<script src="javascripts/jquery.foundation.alerts.js"></script>
	<script src="javascripts/jquery.foundation.topbar.js"></script>
	<script src="javascripts/jquery.foundation.joyride.js"></script>
	<script src="javascripts/jquery.foundation.clearing.js"></script>
	<script src="javascripts/jquery.foundation.magellan.js"></script>
	
</head>
<body>
	<!-- Header and Nav -->
  <div class="row">
    <div class="two columns">
      <h1><img src="images/heroes/<?php print "$currenthero" . "_hphover.png" ?> " /></h1>
	</div>
	<div class="three columns">
	<div class="small button">
	<form class="custom" action="home.php" method="GET">
	  <label for="customDropdown">Select a hero</label>
       <select name="hero">
      <?php 
				$query = "SELECT hero_name, common_name FROM dota2.heroes WHERE id >$1";
				$prepared = pg_prepare($conn, "HeroList",$query);
				$result = pg_execute($conn, "HeroList", array('0'));
					
					
					
				while($rows = pg_fetch_assoc($result)){
						$name = $rows['common_name'];
						$value = $rows['hero_name'];
						print "<option value=$value>$name</option>";
				}
		?>
		</select>
	<input type="submit" value="Go!" class="small button"></input>
	</form>
  </div>
  </div>
	<div class="three columns">
  	<div class="small button">
	<form class="custom" action="home.php" method="GET">
	  <label for="customDropdown">Select a stream or add one</label>
       <select name="stream_id">
      <?php 
				$query = "SELECT stream_name, id FROM twitch.streams WHERE id >$1";
				$prepared = pg_prepare($conn, "StreamList",$query);
				$result = pg_execute($conn, "StreamList", array('0'));
					
					
					
				while($rows = pg_fetch_assoc($result)){
						$stream_name = $rows['stream_name'];
						$stream_id = $rows['id'];
						print "<option value=$stream_id>$stream_name</option>";
				}
		?>
		</select>
	<input type="submit" value="Go!" class="small button"></input>
	</form>
  </div>
  </div>
	<div class="four columns">
      <ul class="nav-bar right">
        <li><a href="home.php">Home</a></li>
        <li><a href="logout.php">Logout</a></li>
      </ul>
    </div>
   </div>
   <div class="row">
	<div class="twelve columns">
		<iframe frameborder="0" 
        scrolling="no" 
        id="chat_embed" 
        src="http://twitch.tv/chat/embed?channel=beyondthesummit&amp;popout_chat=true" 
        height="500" 
        width="350">
</iframe>
	</div>
  </div>
  <div class="row">
    <div class="twelve columns">
    
      <div class="panel">
        <h4>Get in touch!</h4>
            
        <div class="row">
          <div class="nine columns">
            <p>We'd love to hear from you, you attractive person you.</p>
          </div>
          <div class="three columns">
            <a href="#" class="radius button right">Contact Us</a>
          </div>
        </div>
      </div>
      
    </div>
  </div>
 </body>
 </html>