<?php
/*
login_error 			0 --> All OK
						1 --> Incorrect password
						2 --> Incorrect guest password
*/
$target_dir = "./";
$filename = basename($_FILES["fileToUpload"]["name"]);
$target_file = $target_dir . $filename;
$uploadOk = 1;
switch ($_POST["email"])
{
case 'hasilpaudyal@gmail.com':
	$user = 'Hasil';
	if ($_POST["password"] != 'aaaa') $login_error = 1;
	else $login_error = 0;
	break;

case 'neilroxtar94@gmail.com':
	$user = 'Subharun';
	if ($_POST["password"] != 'aaaa') $login_error = 1;
	else $login_error = 0;
	break;

case 'lipikamitra2008@gmail.com':
	$user = 'Lipika';
	if ($_POST["password"] != 'aaaa') $login_error = 1;
	else $login_error = 0;
	break;

case 'swethaanjali25@gmail.com':
	$user = 'Swetha';
	if ($_POST["password"] != 'aaaa') $login_error = 1;
	else $login_error = 0;
	break;

default:
	$user = 'Guest';
	if ($_POST["password"] != 'gguueesstt') $login_error = 2;
	$login_error = 0;
}

if ($login_error == 1) echo 'Incorrect password for ' . $user;
else if ($login_error == 2) echo 'Incorrect Guest password!';
else
{

	// Check File Name

	if ($filename != "DATA.CSV")
	{
		echo "Sorry, only DATA.CSV file is allowed.";
		$uploadOk = 0;
	}

	// if everything is ok, try to upload file

	else
	{

		// Delete DATA.CSV

		unlink($_SERVER['DOCUMENT_ROOT'] . '/performance-analysis/DATA.CSV');
		if (move_uploaded_file($_FILES["fileToUpload"]["tmp_name"], $target_file))
		{ include ($_SERVER['DOCUMENT_ROOT'] . '/performance-analysis/form.html');}
		else
		{
			echo "Sorry, there was an error uploading your file.";
		}
	}
}

?>