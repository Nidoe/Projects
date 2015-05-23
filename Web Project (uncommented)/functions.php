#Database Connection
<?php
	function dbconn(){
		$connectionString = ""
		$connection = pg_connect($connectionString);
		
		return $connection;
	
	}

?>