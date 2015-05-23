<?php
	require("functions.php");
	//If user is already logged in, redirect to home page
	session_start();
	if(isset($_SESSION['loggedin'])){
		header('Location: home.php');
	}
	
	$conn = dbconn();
	
	//Post function on submission of Username and Password
	if(isset($_POST['submit'])){
	
			//Check if both fields are filled
			
			if(isset($_POST['username'], $_POST['password'])){
					//username is stored as lowercase in database on registration
					$username = strtolower($_POST['username']);
					$password = $_POST['password'];
			
					//Prepare authentication query
					$userlookup = "SELECT salt, password_hash FROM dota2.authentication WHERE username = $1";
					$stmt = pg_prepare($conn, "UserLookup", $userlookup);
					
					
					
					//Execute userlookup
					if($stmt){
						$result = pg_execute($conn, "UserLookup", array($username));
						$row = pg_fetch_assoc($result);
						}
					//Trim salt and hash
					$salt = trim($row['salt']);
					
					$pwhash = trim($row['password_hash']);
					
					//Create a hash with the salt and password the user typed in
					$localhash = md5($salt . $password);
					
					//Compare the previous hash to the new hash
					if($localhash == $pwhash){
					
						//Start the user session and redirect to home page
						
						session_start();
						$favherolookup = "SELECT fav_hero FROM dota2.user_info WHERE username = $1";
						$stmt = pg_prepare($conn, "FavHero", $favherolookup);
						
						$result = pg_execute($conn,"FavHero",array($username));
						
						$row = pg_fetch_assoc($result);
						
						
						$_SESSION['username'] = $username;
						$_SESSION['fav_hero'] = $row['fav_hero'];
						$_SESSION['loggedin'] = 1;
						
						header('Location: home.php');
					}
					//Error if authentication fails
					else{
						print "<p>Username and/or Password not found</p>";
					}
			}
		}
?>
<!DOCTYPE html>

<!-- paulirish.com/2008/conditional-stylesheets-vs-css-hacks-answer-neither/ -->
<!--[if lt IE 7]> <html class="no-js lt-ie9 lt-ie8 lt-ie7" lang="en"> <![endif]-->
<!--[if IE 7]>    <html class="no-js lt-ie9 lt-ie8" lang="en"> <![endif]-->
<!--[if IE 8]>    <html class="no-js lt-ie9" lang="en"> <![endif]-->
<!--[if gt IE 8]><!--> <html class="no-js" lang="en"> <!--<![endif]-->
<head>
	<meta charset="utf-8" />

  	<meta name="viewport" content="width=device-width" />

	<title>Log in to Dota 2 Dashboard</title>
  
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
  
  <!-- IE Fix for HTML5 Tags -->
  <!--[if lt IE 9]>
    <script src="http://html5shiv.googlecode.com/svn/trunk/html5.js"></script>
  <![endif]-->


</head>
<body>
	<div class="row heading">
		<div class="columns seven centered"><!--left-->
			<h2>Dota 2 Dashboard Login!</h2>
		</div><!--left-->
		<div class="columns five"><!--right-->
	
		</div><!--right-->
		<hr />
	</div><!--row-->
  
  	<div class="row">
<div class="content columns ten">
  <div class="member_list columns eight centered">
	<h1>Login</h1>
	<p>Please login with your username and password below.</p>
		
	<div id="infoMessage"></div>
	
	<form action="login.php" method="post">		
	  <p>
		<label for="username">Username:</label>
		<input type="text" name="username" value="" id="username"  />	  </p>
	
	  <p>
		<label for="password">Password:</label>
		<input type="password" name="password" value="" id="password"  />	  </p>
			
	  <p><input type="submit" name="submit" value="Login" class="radius button right"  /></p>
		
	</form>	
	<p><a href="forgot_password">Forgot your password?</a></p>
  </div>
</div>
		
		<nav class="two columns">
			<ul class="nav-bar vertical">
										<li>
						<a href="home.php">Home</a>	
					</li>
										<li>
						<a href="about.php">About Us</a>	
					</li>
				<!--logout-->
				                                        <li>
                                                <a href="register.php">Register</a>
                                        </li>
					<li>
						<a href="login.php">Log In&raquo;</a>	
					</li>
								<!--end logout-->

			</ul>
		</nav>
<script>  
$(document).foundationNavigation();  
</script>
<!DOCTYPE html>
<head>
</head>
<body>
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
</body>
</html>
