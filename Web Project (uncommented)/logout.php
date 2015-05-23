<?php
	//Destroy all session variables
	session_start();
	session_destroy();
	
	//Redirect to login page
	
	header('Location: index.html');
?>