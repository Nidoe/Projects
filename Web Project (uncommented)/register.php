<?php

session_start();
if(isset($_SESSION['loggedin'])){
	
	header('Location:home.php');
}

require_once('functions.php');

$conn = dbconn();

if(isset($_POST['submit'])){
	
		//Match both passwords
		
		if($_POST['password'] == $_POST['password_confirm']){
		
			//Sanitize username for proper database input
			
			$username = strtolower($_POST['username']);
			$password = $_POST['password'];
			$email = $_POST['email'];
			$fav_hero = $_POST['fav_hero'];
			
			//Create a random salt and use the salt + password to create a hash
			
			mt_srand();
			$salt = mt_rand();
			$pwhash = md5($salt . $password);
			
			//User_info query adds username, default date value, and a blank value for description to the lab7.user_info table
			
			$userinfoquery = "INSERT INTO dota2.user_info(username, registration_date, fav_hero, email) VALUES ($1, DEFAULT,$2, $3)";
			
			//Authentication query adds the username, hash, and salt to the lab7.authenticaiton table
			
			$authenticationquery =  "INSERT INTO dota2.authentication(username, password_hash, salt) VALUES($1, $2, $3)";
			
			$stmt = pg_prepare($conn, "NewUserInfo", $userinfoquery);
			$stmt2 = pg_prepare($conn, "NewUserAuth",$authenticationquery);
			
			if($stmt){
				$result = pg_execute($conn, "NewUserInfo", array($username,$fav_hero,$email));
				if($result){
					if($stmt2){
						$result2 = pg_execute($conn, "NewUserAuth", array($username, $pwhash, $salt));
						
						$_SESSION['username'] = $username;
						$_SESSION['fav_hero'] = $fav_hero;
						$_SESSION['loggedin'] = 1;
						header('Location:home.php');
					}
				}
				else{
					print "Username Already Exists";
				}
			}

		print "Your passwords do not match!";
		}
}
?>
<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8" />

  	<meta name="viewport" content="width=device-width" />

	<title>Registration for Dota 2 Dashboard</title>
  
  	<link rel="stylesheet" href="stylesheets/foundation.css">
	<link rel="stylesheet" href="stylesheets/foundation.min.css">
	<link rel="stylesheet" href="stylesheets/app.css">

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
	
   <script>
   function showimage(str){
		if(str ==""){
			document.getElementById("image").innerHTML="";
			return;
		}
		if (window.XMLHttpRequest){
			// code for IE7+, Firefox, Chrome, Opera, Safari
			xmlhttp=new XMLHttpRequest();
		}
		else{
			// code for IE6, IE5
			xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
		}
		xmlhttp.onreadystatechange=function(){
			if (xmlhttp.readyState==4 && xmlhttp.status==200){
				document.getElementById("image").innerHTML=xmlhttp.responseText;
			}
		}
		xmlhttp.open("GET","getimage.php?q="+str,true);
		xmlhttp.send();
	
	}
	</script>
</head>

<body>
<div class="row heading">
	<div class="nine columns centered">
		<h2>Dota 2 Dashboard Registration! </h2>
	</div>
	<hr />
</div>


<div class="row">
<div class="content columns ten">
  <div class="columns eight centered">
	<h1>Registration</h1>
	<p>Please enter the users information below.</p>
	
	<div id="infoMessage">
</div>
	
	<form action="register.php" method="post">	
		  <p>
				Username: <br />
				<input type="text" name="username" value="" id="username"  />		  </p>
	
		  <p>
				Email: <br />
				<input type="text" name="email" value="" id="email"  />		  </p>
		  <p>	Favorite Hero: <br />
				<select name="fav_hero" onchange="showimage(this.value)">
				<option></option>
				<?php 
					$query = "SELECT hero_name, common_name FROM dota2.heroes WHERE id >$1";
					$prepared = pg_prepare($conn, "HeroList",$query);
					$result = pg_execute($conn, "HeroList", array('0'));
					
					
					
					while($rows = pg_fetch_assoc($result)){
						$name = $rows['common_name'];
						$value = $rows['hero_name'];
						print "<option name=\"$name\" value=$value>$name</option>";
					}
				?>
				</select></p>
		  <p id="image">
			</p>
		  <p>
				Password: <br />
				<input type="password" name="password" value="" id="password"  />		  </p>
	
		  <p>
				Confirm Password: <br />
				<input type="password" name="password_confirm" value="" id="password_confirm"  />		  </p>
	
		  <p><input type="submit" name="submit" value="Register" class="radius button right"  /></p>
	
	</form>  </div>
</div>
		
		<nav class="two columns">
	<ul class="nav-bar vertical">
		<li><a href="home.php">Home</a></li>
		<li><a href="about.php">About</a></li>
		<li><a href="register.php">Register</a></li>
		<li><a href="login.php">Log In&raquo;</a></li>
	</ul>
</nav>
<div class="row">
    <div class="twelve columns">
	  <br><br>
      <div class="panel">
        <h4>Get in touch!</h4>

        <div class="row">
          <div class="nine columns">
            <p>We would love to hear from you if you have any questions about our services.</p>
          </div>
          <div class="three columns">
            <a href="#" class="radius button right">Contact Us</a>
          </div>
        </div>
      </div>

    </div>
  </div>	