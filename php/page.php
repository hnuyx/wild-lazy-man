<html>
<head>
	<meta http-equiv="Content-type" content="text/html; charset=utf-8" />
</head>
<style>
	body
	{
		font-size: 12px;
		font-family: verdana;
		width: 100%;
	}

	div.page
	{
		text-align: center;
	}
	div.page a
	{
		border:#aaaadd 1px solid;
		text-decoration: none;
		padding: 2px 5px 2px 5px;
		margin: 2px;
	}

	div.page span.current
	{
		border: #000099 1px solid;
		background-color: #000099;
		padding: 4px 6px 4px 6px;
		margin: 2px;
		color: #fff;
		font-weight: bold;
	}

	div.page span.disable
	{
		border: #eee 1px solid;
		padding: 2px 5px 2px 5px;
		margin: 2px;
		color: #ddd;
	}

	div.page form
	{
		display: inline;
	}

</style>
<body>
<?php
	// get page number
	$page = $_GET['p'];

	// database info
	$host = "localhost";
	$username = "testusr";
	$password = "testpwd";
	$db = "testdb";

	// connnect to mysql
	$conn = mysql_connect($host, $username, $password);
	if(!$conn)
	{
		echo "mysql connnect failed";
		exit;
	}

	// set database
	mysql_select_db($db, $conn);
	// set character
	mysql_query("SET NAMES UTF8");

	// get data
	$psize = 30;
	$start=($page-1) * $psize;
	$sql = "SELECT * FROM grey LIMIT $start, $psize";
	$result = mysql_query($sql, $conn);

	// content
	echo "<div class='content'>";
	// table
	echo "<table border=1 cellspacing=0 width=60% align=center>";
	echo "<tr>";
		echo "<td>Cg</td>";
		echo "<td>Recv</td>";
		echo "<td>Send</td>";
	echo "</tr>";
	while($row = mysql_fetch_array($result))
	{
		echo "<tr>";
		// get data
		$cg = $row['cg'];
		$recv = $row['recv'];
		$send = $row['send'];

		// show data
		echo "<td>$cg</td>";
		echo "<td>$recv</td>";
		echo "<td>$send</td>";

		echo "</tr>";
	}
	echo "</table></div>";
	// free resource
	mysql_free_result($result);

	// get total number
	$sql = "SELECT COUNT(*) FROM grey";
	$total_res = mysql_fetch_array(mysql_query($sql, $conn));
	$total = $total_res[0];

	// pages
	$total_pages = ceil($total/$psize);

	// page bar
	$page_bar = "<br/><div class='page'>";
	// prev page
	if($page > 1)
	{
		$page_bar .= "<a href='".$_SERVER['PHP_SELF']."?p=1'>Head</a>";
		$page_bar .= "<a href='".$_SERVER['PHP_SELF']."?p=".($page-1)."'>Prev</a>";
	}
	else
	{
		$page_bar .= "<span class='disable'>Head</span>";
		$page_bar .= "<span class='disable'>Prev</span>";
	}

	// show page
	$show_page = 11;
	$page_offset = ($show_page - 1)/2;
	$start = 1;
	$end = $total_pages;
	if($total_pages > $show_page)
	{
		// get start
		if($page > $page_offset)
		{
			$start = $page - $page_offset;
		}

		// get end
		if($page + $page_offset < $total_pages)
		{
			$end = $page + $page_offset;
		}

		// revise end
		if(1 == $start)
		{
			$end = $show_page;
		}

		// revise start
		if($total_pages == $end)
		{
			$start = $total_pages - $show_page + 1;
		}
	}

	// need ...
	if($start > 1)
	{
		$page_bar .="...";
	}

	// show page
	for($i = $start; $i <= $end; $i ++)
	{
		if($page == $i)
		{
			$page_bar .= "<span class='current' >$i</span>";
		}
		else
		{
			$page_bar .= "<a href=".$_SERVER['PHP_SELF']."?p=".$i."'>$i</a>";
		}
	}

	// need ...
	if($end < $total_pages)
	{
		$page_bar .="...";
	}


	// next page
	if($page < $total_pages)
	{
		$page_bar .= "<a href='".$_SERVER['PHP_SELF']."?p=".($page+1)."'>Next</a>";
		$page_bar .= "<a href='".$_SERVER['PHP_SELF']."?p=".($total_pages)."'>Tail</a>";
	}
	else
	{
		$page_bar .= "<span class='disable'>Next</span>";
		$page_bar .= "<span class='disable'>Tail</span>";
	}
	$page_bar .= " Total $total_pages";

	// jump
	$page_bar .= ", <form action='".$_SERVER['PHP_SELF']."' method='get'>";
	$page_bar .= "To <input type='text' size='2' name='p' value='".$page."'/>";
	$page_bar .= "<input type='submit' value='Go' />";
	$page_bar .= "</form></div>";

	// show page bar
	echo "$page_bar";

	// close connect
	mysql_close($conn);
?>
</body>
</html>
