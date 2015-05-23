<html>
<title>Lab1</title>
<body>
<?php
echo (date("l dS \of F Y h:i:s A") . "<br />");
echo $_SERVER['REMOTE_ADDR'];
echo $_SERVER['HTTP_USER_AGENT'];
?>

<table border="1">
<form action="Lab1.php" method="POST">
	<tr>
	<td>
		<h3>Student Name:</h3>
	</td>
	<td>
		<input type="text" name="name" value=>
	</td>
	</tr>
	<tr>
	<td><h3>Password:</h3></td>
	<td><input type="password" name="password" value=></td>
	</tr>
	<tr>
	<td><h3>Gender:</h3></td>
	<td><input type="radio" name="gender" value="Male" />Male<br />
	    <input type="radio" name="gender" value="Female" />Female</td>
       </tr>
	<tr>
	<td><h3>Class:</h3></td>
	<td><select name="Class">
		<option></option>
		<option value="FR">FR</option>
		<option value="SO">SO</option>
		<option value="JR">JR</option>
		<option value="SR">SR</option>
	    </select></td>
	</tr>
	</table>
	<input type="submit" value="Submit" />
	<br />
</form>
<?php
	if($_POST['name'] != NULL){
		echo "Student Name: " . $_POST['name'];
		echo "<br />";
	}
	if($_POST['gender'] != NULL){
		echo "Gender: " . $_POST['gender'];
		echo "<br />";
	}
	if($_POST['Class'] != NULL){
		if($_POST['Class'] == "FR"){
			$classlevel = "Freshman";
		}
		if($_POST['Class'] == "SO"){
			$classlevel = "Sophmore";
		}
		if($_POST['Class'] == "JR"){
			$classlevel = "Junior";
		}
		if($_POST['Class'] == "SR"){
			$classlevel = "Senior";
		}
		echo "Class Level: " . $classlevel;
		echo "<br />";
	}

?>
</body>
</html>

