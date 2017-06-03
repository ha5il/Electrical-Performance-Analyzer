<?php
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
	$login_error = 1;
}

if ($login_error == 1) echo 'Login error :( <br /> Probably incorrect password!';
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
		{
			print ('<html><head><meta content="text/html; charset=UTF-8"http-equiv=Content-Type><meta content="width=device-width,initial-scale=1,maximum-scale=1,user-scalable=no"name=viewport><link href=/assets/logo.png rel="shortcut icon"><link href=https://cdnjs.cloudflare.com/ajax/libs/materialize/0.98.2/css/materialize.min.css rel=stylesheet><style media=screen,projection rel=stylesheet>nav{background-color:#8e4585}</style><meta content="width=device-width,initial-scale=1"name=viewport><title>Enter Analysis Limits</title></head><body><nav><div class=nav-wrapper><ul class="hide-on-med-and-down left"><li class=active><a href=#!>Electrical Performance Analysis</a></ul><ul class=side-nav id=slide-out><li><a href=#!>Electrical Performance Analysis</a></ul><a href=# class=button-collapse data-activates=slide-out><i class="fontsize mdi-navigation">Menu</i></a></div></nav><div class=container style=text-align:center><h5>Hello ');
			echo $user;
			print ('<br />Enter the parameters for analysis<br /></h5> <div class=row><form action=analysis.php class="col s12"method=post><div class=row><div class="col input-field s6"><input name=mxtempr type=number value=45 class=validate><label>Max Temperature</label></div><div class="col input-field s6"><input name=mntempr type=number value=25 class=validate><label>Min Temperature</label></div><div class="col input-field s6"><input name=mxvtg type=number value=1.5 class=validate><label>Max Voltage</label></div><div class="col input-field s6"><input name=mnvtg type=number value=1.0><label>Min Voltage</label></div><div class="col input-field s6"><input name=mxcrt type=number value=200><label>Max Current</label></div><div class="col input-field s6"><input name=mncrt type=number value=100><label>Min Current</label></div><div class="col input-field s6"><input name=mxspd type=number value=1100><label>Max Speed</label></div><div class="col input-field s6"><input name=mnspd type=number value=900><label>Min Speed</label></div></div><button class="btn waves-effect waves-red"type="submit">Analyse</button></form></div></div><script src=https://code.jquery.com/jquery-2.1.1.min.js></script><script src=https://cdnjs.cloudflare.com/ajax/libs/materialize/0.98.2/js/materialize.min.js></script><script>$(".button-collapse").sideNav();</script></body></html>');
		}
		else
		{
			echo "Sorry, there was an error uploading your file.";
		}
	}
}

?>