<?php
	// get page number
	$page = $_GET['p'];

	// database info
	$host = "192.168.4.96";
	$username = "root";
	$password = "Lj#123456";
	$db = "test";

	// connnect to mysql
	$conn = mysql_connect($host, $username, $password);
	if(!$conn){
		echo "mysql connnect failed";
		exit;
	}

	// set database
	mysql_select_db($db);
	// set character
	mysql_query("SET NAMES UTF8");

	// get data
	$paize=30;
	$start=($page-1) * $psize;
	$sql = "SELECT * FROM grey LIMIT $start, $psize";
	$result = mysql_query($sql);

	// table
	echo "<table border=1 cellspacing=0 with=60%>";
	echo "<tr>";
		echo "<td>Cg</td>";
		echo "<td>Recv</td>";
		echo "<td>Send</td>";
	echo "</tr>";
	while($row = mysql_fetch_assoc($result)){
		echo "<tr>";
		//echo "<td>($row['cg'])</td>";
		//echo "<td>($row['recv'])</td>";
		//echo "<td>($row['send'])</td>";
		echo "</tr>";
	}
	echo "</table>";

	mysql_free_result($result);
	mysql_close($conn);
?>
