<!DOCTYPE html>
<html>
<head>

	<title>TEST</title>

<link href="//maxcdn.bootstrapcdn.com/bootstrap/4.1.1/css/bootstrap.min.css" rel="stylesheet" id="bootstrap-css">
<script src="//maxcdn.bootstrapcdn.com/bootstrap/4.1.1/js/bootstrap.min.js"></script>
<script src="//cdnjs.cloudflare.com/ajax/libs/jquery/2.2.4/jquery.min.js"></script>

</head>
<body>

	<?php
		$url = 'https://jsonplaceholder.typicode.com/users'; // Path to JSON File
		$data = file_get_contents($url); // Put file contents in a variable
		// $characters = json_decode($data); // Decode JSON feed
		$characters = json_decode($data, true); // Decode JSON feed and make an associative array


		// echo $characters[0]->name; // Echo first name

		// Echo all names

		?>


		<br/>

		<div class="container">

		<h2>API Test</h2>

		

		<table class="table-bordered">
		<tbody>
			<tr>
				<th>ID</th>
				<th>Name</th>
				<th>Email</th>
				<th>Street</th>
			</tr>
			<?php foreach ($characters as $character) : ?>
	        <tr>
	            <td> <?php echo $character['id']; ?> </td>
	            <td> <?php echo $character['name']; ?> </td>
	            <td><?php echo $character['email']; ?></td>
	            <td><?php echo $character['address']['street'] ?></td>
	        </tr>
			<?php endforeach; ?>
		</tbody>
	</table>

	</div>


</body>
</html>
