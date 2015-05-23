<?PHP
        session_cache_limiter(‘private, must-revalidate’);
        session_start(); 
?>
<html>
<title>Lab2B</title>
<body>
<?PHP
		if(isset($_POST['flag'])){
			unset($_SESSION['lrsfh3']);
		}
		if(isset($_SESSION['lrsfh3'])){
		echo $_SESSION['lrsfh3'] . " is logged in.";
		$cols = $_SESSION['cols'];
		$rows = $_SESSION['rows'];
		echo '<table border="1">';
			for($i=0; $i < $rows; $i++){
				echo "<tr>\n";
					for($j=0; $j < $cols;$j++){
						echo "<td>";
						echo rand(1,100);
						echo "</td>";
					}
				echo "</tr>";
			}
		echo '</table>';
		echo "<form action='Lab2B.php' method='POST'>
			<input type='hidden' name='flag' value='1'>
			<input type='submit' value='Log out' />";
		}
		
		else{
			echo 'You are not logged in. ';
			echo '<a href="Lab2A.php">Click here to log in...</a>';
		}
		
		
		?>
</body>
</html>
