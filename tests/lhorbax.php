<!DOCTYPE html>
<html>
  <head>
    <title>PHP GET and POST Method Example</title>
	
	<!-- include css file here-->
    <link rel="stylesheet" href="css/style.css"/>
   
	<!-- include JavaScript file here-->
	<script src="http://ajax.googleapis.com/ajax/libs/jquery/1.11.1/jquery.min.js"></script>
	<script type="text/javascript" src="js/metode.js"></script>
  
  </head>	
  <body>
	<div class="container">
		<div class="main">
	      <form  method="get" action="index.php" id="form">
			
			<label>name :</label>
			<input type="text" name="fnama" id="fnama" />
			
			<label>lhorba :</label>
			<input type="text" name="lalamat" id="lalamat" />
			
			<label>hhhhhh :</label>
			<span><input type="radio" name="method" value="get" checked> GET &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
			<input type="radio" name="method" value="post" > POST </span>	
			
			<input type="submit" name="submit" id="submit" value="Submit">
		  </form>
		</div>
		<?php 
		if(isset($_POST['fnama']))
		{
		$fnama = $_POST['fnama'];
		$lalamat = $_POST['lalamat'];
		echo "<span class='success'>Dengan <b>METODE POST</b></span><br/>";
		echo "Nama : ".$fnama."<br/>Alamat : ".$lalamat;
		}
		//--------------------------------------------------------------------
		if(isset($_GET['fnama']))
		{
		$fnama = $_GET['fnama'];
		$lalamat = $_GET['lalamat'];
		echo "<span class='success'>Dengan <b>METODE GET</b></span><br/>";
		echo "Nama : ".$fnama."<br/>Alamat : ".$lalamat;
		}
		?>
   </div>

  </body>
</html>
