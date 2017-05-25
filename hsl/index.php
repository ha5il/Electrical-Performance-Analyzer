<html>
   <head>
      <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" >
      <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1.0, user-scalable=no" >
	  
     <!-- <link href="/assets/logo.png" rel="shortcut icon"> -->
	 
      <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/materialize/0.98.2/css/materialize.min.css">
      <style type="text/css" media="screen,projection" rel="stylesheet"> nav {background-color: #8E4585}</style>
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

// Main Program
$row = 1;
$skipCount=0;
$errorCount=0;
if (($handle = fopen("DATA.CSV", "r")) !== FALSE)
{
 while (($data = fgetcsv($handle, ",")) !== FALSE)
 {
  $num = count($data);					// Counting the number of data and it has to be 4
  if ($num != 4)
  {
   $skipCount++;
   $skippedRow[$skipCount] = $row;
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
 //  echo "High temperature $data[0] degree Celsius found on row $row <br />";
   $t[$row] = 3;
  }
   else if ($data[0] < $temperature_min)
  {
 //  echo "Low temperature $data[0] degree Celsius found on row $row <br />";
   $t[$row] = 1;
  }
  else
  {
   $t[$row] = 2;
  }


  // Checking Voltage
  if ($data[1] > $voltage_max)
  {
 //  echo "High voltage $data[1] V found on row $row <br />";
   $v[$row] = 3;
  }
  else if ($data[1] < $voltage_min)
  {
 //  echo "Low voltage $data[1] V found on row $row <br />";
   $v[$row] = 1;
  }
    else
  {
   $v[$row] = 2;
  }
  // Checking Current
  if ($data[2] > $current_max)
  {
 //  echo "High current $data[2] mA found on row $row <br />";
   $c[$row] = 3;
  }
  else if ($data[2] < $current_min)
  {
 //  echo "Low current $data[2] mA found on row $row <br />";
   $c[$row] = 1;
  }
    else
  {
   $c[$row] = 2;
  }

    // Checking Speed
  if ($data[3] > $speed_max)
  {
 //  echo "High speed $data[3] RPM found on row $row <br />";
   $s[$row] = 3;
  }
  else if ($data[3] < $speed_min)
  {
  // echo "Low speed $data[3] RPM found on row $row <br />";
   $s[$row] = 1;
  }
    else
  {
   $s[$row] = 2;
  }
 if ($t[$row] . $v[$row] . $c[$row] . $s[$row] != 2222)          // if all parameters aren't normal i.e., 2222
 {
   $errorCount++;
   $errorRow [$errorCount] = $row;
   $errors[$errorCount] = $t[$row] . $v[$row] . $c[$row] . $s[$row];
 }
  $row++;
 }
 fclose($handle);
 
 // Including the data processor php
include ($_SERVER['DOCUMENT_ROOT'] . '/project/hsl/process.php'); 
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