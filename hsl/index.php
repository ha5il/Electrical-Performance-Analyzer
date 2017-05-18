<html>
   <head>
      <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" >
      <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1.0, user-scalable=no" >
	  
     <!-- <link href="/assets/logo.png" rel="shortcut icon"> -->
	 
      <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/materialize/0.98.2/css/materialize.min.css">
<link href="https://fonts.googleapis.com/css?family=Handlee" rel="stylesheet">
      <style type="text/css" media="screen,projection" rel="stylesheet"> body {font-family: 'Handlee', cursive; } nav {background-color: #8E4585}</style>
      <meta name="viewport" content="width=device-width, initial-scale=1.0"/>
      <title>Performance Analysis</title>
   </head>
  <body>
      <nav>
         <div class="nav-wrapper">
            <ul class="left hide-on-med-and-down">
               <li class="active"><a href="#!">Electrical Performance Analysis</a></li>
            </ul>
            <ul id="slide-out" class="side-nav">
               <li><a href="#!">Electrical Performance Analysis</a></li>

            </ul>
            <a href="#" data-activates="slide-out" class="button-collapse"><i class="mdi-navigation fontsize">Menu</i></a> 
         </div>
      </nav>
	  
	    <div class="container">
	   <center><h4>The DATA.CSV file has to be stored on server first!</h4></center>
	  
	  <h5>
<?php
// Fetching the Standard Values
include ($_SERVER['DOCUMENT_ROOT'] . '/project/hsl/data.php');

// Calculating the maximum values as per tolerance value
$temperature_max = (1 + $temperature_tol / 100) * $temperature;
$voltage_max = (1 + $temperature_tol / 100) * $temperature;
$current_max = (1 + $temperature_tol / 100) * $temperature;
$speed_max = (1 + $temperature_tol / 100) * $temperature;
// Calculating the minimum values as per tolerance value
$temperature_min = (1 - $temperature_tol / 100) * $temperature;
$voltage_min = (1 - $temperature_tol / 100) * $temperature;
$current_min = (1 - $temperature_tol / 100) * $temperature;
$speed_min = (1 - $temperature_tol / 100) * $temperature;
// Main Program
$row = 1;
if (($handle = fopen("DATA.CSV", "r")) !== FALSE)
{
 while (($data = fgetcsv($handle, ",")) !== FALSE)
 {
  $num = count($data);
  if ($num !== 4)
  {
   echo "<br />$num data found in line $row. These data are skipped during analysis... <br />";
   for ($c = 0; $c < $num; $c++)
   {
    echo $data[$c] . "<br />";
   }
   $row++;
   continue;
  }
  // Do the analysis as data is always 4
  if ($data[0] == 'Temperature')
  {
   $row++;
   continue;
  }
  // Checking Temperature
  if ($data[0] > $temperature_max)
  {
   echo "High temperature $data[0] degree Celsius found on row $row <br />";
  }
  if ($data[0] < $temperature_min)
  {
   echo "Low temperature $data[0] degree Celsius found on row $row <br />";
  }
  // Checking Voltage
  if ($data[1] > $voltage_max)
  {
   echo "High voltage $data[1] V found on row $row <br />";
  }
  if ($data[1] < $voltage_min)
  {
   echo "Low voltage $data[1] V found on row $row <br />";
  }
  // Checking Current
  if ($data[2] > $current_max)
  {
   echo "High current $data[2] mA found on row $row <br />";
  }
  if ($data[2] < $current_min)
  {
   echo "Low current $data[2] mA found on row $row <br />";
  }
  // Checking Speed
  if ($data[3] > $speed_max)
  {
   echo "High speed $data[3] RPM found on row $row <br />";
  }
  if ($data[3] < $speed_min)
  {
   echo "Low speed $data[3] RPM found on row $row <br />";
  }
  $row++;
 }
 fclose($handle);
}
else echo "DATA.CSV not found on the server";
?>
</h5>
 </div>
      <script type="text/javascript" src="https://code.jquery.com/jquery-2.1.1.min.js"></script>
      <script src="https://cdnjs.cloudflare.com/ajax/libs/materialize/0.98.2/js/materialize.min.js"></script>
      <script>    $(".button-collapse").sideNav();</script>
   </body>
</html>