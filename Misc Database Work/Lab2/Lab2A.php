<?PHP
        session_cache_limiter(‘private, must-revalidate’);
        session_start(); 
?>
<html>
<title>Lab2A</title>
<body>
<?PHP
if($_POST['name'] != NULL){
	$_SESSION['lrsfh3'] = $_POST['name'];
	$_SESSION['rows'] = $_POST['Rows'];
	$_SESSION['cols'] = $_POST['Columns'];
	echo $_SESSION['lrsfh3'] . " is now logged in.";
	echo '<br /><a href="Lab2B.php">Click here to continue...</a>';
}
else{
	echo "<table border='1'>
			<form action='Lab2A.php' method='POST'>
			<tr>
			<td>Login Name:</td>
		<td colspan='3'>
		<input type='text' name='name' value=>
		</td>
		</tr>
		<tr>
		<td>Number of Rows</td>
		<td><select name='Rows'>
		<option value='5'>5</option>
		<option value='6'>6</option>
		<option value='7'>7</option>
		<option value='8'>8</option>
		<option value='9'>9</option>
		<option value='10'>10</option>
	    </select></td>
		<td>Number of Columns</td>
		<td><select name='Columns'>
		<option value='5'>5</option>
		<option value='6'>6</option>
		<option value='7'>7</option>
		<option value='8'>8</option>
		<option value='9'>9</option>
		<option value='10'>10</option>
	    </select></td>
		</tr>
		</table>
		<input type='submit' value='Log in' />
	<br />
	</form>";
	}
?>
</body>
</html>
