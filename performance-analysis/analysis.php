<?php
$row = 1;

// Fetching the Standard Values

$temperature_max = $_POST["mxtempr"];
$voltage_max = $_POST["mxvtg"];
$current_max = $_POST["mxcrt"];
$speed_max = $_POST["mxspd"];
$temperature_min = $_POST["mntempr"];
$voltage_min = $_POST["mnvtg"];
$current_min = $_POST["mncrt"];
$speed_min = $_POST["mnspd"];

// Main Program

$skipCount = 0;
$errorCount = 0;

if (($handle = fopen("DATA.CSV", "r")) !== FALSE)
{
	while (($data = fgetcsv($handle, ",")) !== FALSE)
	{
		$num = count($data); // Counting the number of data and it has to be 5
		if ($num != 5)
		{
			$skipCount++;
			$skippedRow[$skipCount] = $row;
			$row++;
			continue;
		}

		// Do the analysis as data is always 5

		if ($data[0] == 'Time')
		{
			$row++;
			continue;
		}

		// Recording Time

		$time[$row] = $data[0];

		// Checking Temperature

		if ($data[1] > $temperature_max)
		{
			$t[$row] = 3;
		}
		else
		if ($data[1] < $temperature_min)
		{
			$t[$row] = 1;
		}
		else
		{
			$t[$row] = 2;
		}

		// Checking Voltage

		if ($data[2] > $voltage_max)
		{
			$v[$row] = 3;
		}
		else
		if ($data[2] < $voltage_min)
		{
			$v[$row] = 1;
		}
		else
		{
			$v[$row] = 2;
		}

		// Checking Current

		if ($data[3] > $current_max)
		{
			$c[$row] = 3;
		}
		else
		if ($data[3] < $current_min)
		{
			$c[$row] = 1;
		}
		else
		{
			$c[$row] = 2;
		}

		// Checking Speed

		if ($data[4] > $speed_max)
		{
			$s[$row] = 3;
		}
		else
		if ($data[4] < $speed_min)
		{
			$s[$row] = 1;
		}
		else
		{
			$s[$row] = 2;
		}

		if ($t[$row] . $v[$row] . $c[$row] . $s[$row] != 2222) // if all parameters aren't normal i.e., 2222
		{
			$errorCount++;
			$errorTime[$errorCount] = $time[$row];
			$errors[$errorCount] = $t[$row] . $v[$row] . $c[$row] . $s[$row];
		}

		$row++;
	}

	fclose($handle);
}

function tostring($data)
{
	$splitted = array_map('intval', str_split($data, 2));
	if ($splitted[3] < 10) $splitted[3] = '0' . $splitted[3];
	if ($splitted[4] < 10) $splitted[4] = '0' . $splitted[4];
	if ($splitted[5] < 10) $splitted[5] = '0' . $splitted[5];
	if ($splitted[6] < 10) $splitted[6] = '0' . $splitted[6]; // Converted to double digit
	return ("$splitted[3] " . tomonth($splitted[2]) . " $splitted[0]" . "$splitted[1]" . ' at ' . "$splitted[4]" . ':' . "$splitted[5]" . ":" . "$splitted[6]");
}

function tomonth($mnth)
{
	if ($mnth == 01) return January;
	else
	if ($mnth == 02) return 'February';
	else
	if ($mnth == 03) return 'March';
	else
	if ($mnth == 04) return 'April';
	else
	if ($mnth == 05) return 'May';
	else
	if ($mnth == 06) return 'June';
	else
	if ($mnth == 07) return 'July';
	else
	if ($mnth == 8) return 'August';
	else
	if ($mnth == 9) return 'September';
	else
	if ($mnth == 10) return 'Octuber';
	else
	if ($mnth == 11) return 'November';
	else
	if ($mnth == 12) return 'December';
}
?>
 
 <html>
   <head>
      <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" >
      <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1.0, user-scalable=no" >
	  <link href=/assets/logo.png rel="shortcut icon">
      <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/materialize/0.98.2/css/materialize.min.css">
      <style type="text/css" media="screen,projection" rel="stylesheet"> nav {background-color: #8E4585}</style>
      <meta name="viewport" content="width=device-width, initial-scale=1.0"/>
      <title>Performance Analysis</title>
   </head>
  <body>
      <nav>
         <div class="nav-wrapper">
            <ul class="left hide-on-med-and-down">
               <li class="active tooltipped" data-position="bottom" data-delay="50" data-tooltip="Analyse New Data!"><a href="/performance-analysis/">Electrical Performance Analysis</a></li>
            </ul>
            <ul id="slide-out" class="side-nav">
               <li><a href="/performance-analysis/">Analyse New Data</a></li>

            </ul>
            <a href="#" data-activates="slide-out" class="button-collapse"><i class="mdi-navigation fontsize">Menu</i></a> 
         </div>
      </nav>
	  
	    <div class="container" style="text-align:center">
	   <center><h4><?php if ($row == 1) echo ("Error in DATA.CSV, make sure it exists!"); else echo ("DATA.CSV successfully processed!");?></h4></center>
	  
	              <div class="card-panel hoverable">
               <div class="row">
                  <div class="col s12">
                     <ul class="tabs">
                        <li class="tab col s3 tooltipped" data-position="bottom" data-delay="50" data-tooltip="Analysis Report"><a href="#report"><b>Brief Report</b></a></li>
                        <li class="tab col s3 tooltipped" data-position="bottom" data-delay="50" data-tooltip="All Fluctuations Found"><a href="#fluctuations"><b>All Fluctuations</b></a></li>
                        <li class="tab col s3 tooltipped" data-position="bottom" data-delay="50" data-tooltip="Skips on CSV file"><a href="#skips"><b>Skips</b></a></li>
						<li class="tab col s3 tooltipped" data-position="bottom" data-delay="50" data-tooltip="Our Project Module"><a href="#module"><b>About project</b></a></li>
                     </ul>
                  </div>
               </div>
<div id="report">
<?php
 include ($_SERVER['DOCUMENT_ROOT'] . '/performance-analysis/report.php');
?>
</div>
<div id="fluctuations">
<?php
include ($_SERVER['DOCUMENT_ROOT'] . '/performance-analysis/fluctuations.php');
?>
</div>
<div id="skips">
<?php
include ($_SERVER['DOCUMENT_ROOT'] . '/performance-analysis/skips.php');
?>
</div>
<div id="module">
<!-- All From Word -->

<div class=WordSection1>

<p class=MsoNormal align=center style='margin-bottom:6.0pt;text-align:center'><span
style='mso-no-proof:yes'><v:shapetype id="_x0000_t75" coordsize="21600,21600"
 o:spt="75" o:preferrelative="t" path="m@4@5l@4@11@9@11@9@5xe" filled="f"
 stroked="f">
 <v:stroke joinstyle="miter"/>
 <v:formulas>
  <v:f eqn="if lineDrawn pixelLineWidth 0"/>
  <v:f eqn="sum @0 1 0"/>
  <v:f eqn="sum 0 0 @1"/>
  <v:f eqn="prod @2 1 2"/>
  <v:f eqn="prod @3 21600 pixelWidth"/>
  <v:f eqn="prod @3 21600 pixelHeight"/>
  <v:f eqn="sum @0 0 1"/>
  <v:f eqn="prod @6 1 2"/>
  <v:f eqn="prod @7 21600 pixelWidth"/>
  <v:f eqn="sum @8 21600 0"/>
  <v:f eqn="prod @7 21600 pixelHeight"/>
  <v:f eqn="sum @10 21600 0"/>
 </v:formulas>
 <v:path o:extrusionok="f" gradientshapeok="t" o:connecttype="rect"/>
 <o:lock v:ext="edit" aspectratio="t"/>
</v:shapetype><v:shape id="Picture_x0020_0" o:spid="_x0000_i1026" type="#_x0000_t75"
 alt="index.jpg" style='width:94.5pt;height:113.25pt;visibility:visible;
 mso-wrap-style:square'>
 <v:imagedata src="About_Project_files/image002.jpg" o:title="index"/>
</v:shape></span><span style='font-size:14.0pt;mso-bidi-font-size:11.0pt;
font-family:"Times New Roman",serif;mso-no-proof:yes'><v:shape id="Picture_x0020_1"
 o:spid="_x0000_i1025" type="#_x0000_t75" alt="http://newhorizonindia.edu/nhengineering/wp-content/uploads/2017/05/logo-nhce-1-1.png"
 style='width:165.75pt;height:103.5pt;visibility:visible;mso-wrap-style:square'>
 <v:imagedata src="About_Project_files/image003.png" o:title="logo-nhce-1-1"
  cropleft="18824f" cropright="18678f"/>
</v:shape></span></p>

<p class=MsoNormal style='margin-bottom:0cm;margin-bottom:.0001pt'><b
style='mso-bidi-font-weight:normal'><span style='font-size:18.0pt;mso-bidi-font-size:
16.0pt;font-family:"Times New Roman",serif;color:#943634;mso-themecolor:accent2;
mso-themeshade:191'><o:p>&nbsp;</o:p></span></b></p>

<p class=MsoNormal align=center style='margin-bottom:0cm;margin-bottom:.0001pt;
text-align:center'><b style='mso-bidi-font-weight:normal'><span
style='font-size:18.0pt;mso-bidi-font-size:16.0pt;font-family:"Times New Roman",serif;
color:#943634;mso-themecolor:accent2;mso-themeshade:191'>“ELECTRICAL
PERFORMANCE ANALYSER”<o:p></o:p></span></b></p>

<p class=MsoNormal style='margin-bottom:0cm;margin-bottom:.0001pt;line-height:
115%'><span style='font-size:14.0pt;mso-bidi-font-size:13.0pt;line-height:115%;
font-family:"Times New Roman",serif;color:#984806;mso-themecolor:accent6;
mso-themeshade:128'><o:p>&nbsp;</o:p></span></p>

<p class=MsoNormal align=center style='margin-bottom:0cm;margin-bottom:.0001pt;
text-align:center;line-height:115%'><span style='font-size:14.0pt;mso-bidi-font-size:
13.0pt;line-height:115%;font-family:"Times New Roman",serif;color:red'>UNDER
THE GUIDANCE OF<o:p></o:p></span></p>

<p class=MsoNormal align=center style='margin-bottom:0cm;margin-bottom:.0001pt;
text-align:center;line-height:115%'><span style='font-size:17.0pt;line-height:
115%;font-family:"Times New Roman",serif;color:red'><o:p>&nbsp;</o:p></span></p>

<p class=MsoNormal align=center style='margin-bottom:0cm;margin-bottom:.0001pt;
text-align:center;line-height:115%'><b style='mso-bidi-font-weight:normal'><span
style='font-size:16.0pt;line-height:115%;font-family:"Times New Roman",serif;
color:#002060'>PROF. ANITHA A.</span></b><span style='font-size:14.0pt;
mso-bidi-font-size:17.0pt;line-height:115%;font-family:"Times New Roman",serif'><o:p></o:p></span></p>

<p class=MsoNormal align=center style='margin-bottom:0cm;margin-bottom:.0001pt;
text-align:center'><span style='font-size:14.0pt;mso-bidi-font-size:11.0pt;
font-family:"Times New Roman",serif'><o:p>&nbsp;</o:p></span></p>

<p class=MsoNormal align=center style='text-align:center'><span
style='font-size:14.0pt;mso-bidi-font-size:16.0pt;font-family:"Times New Roman",serif;
color:red'>BY<o:p></o:p></span></p>

<p class=MsoNormalCxSpMiddle align=center style='text-align:center'><b
style='mso-bidi-font-weight:normal'><span style='font-size:14.0pt;font-family:
"Times New Roman",serif;color:#002060'>HASIL PAUDYAL <span style='mso-tab-count:
5'>                                             </span>1NH13EE014<o:p></o:p></span></b></p>

<p class=MsoNormalCxSpMiddle align=center style='text-align:center'><b
style='mso-bidi-font-weight:normal'><span style='font-size:14.0pt;font-family:
"Times New Roman",serif;color:#002060'>LIPIKA MITRA <span style='mso-tab-count:
6'>                                                 </span>1NH13EE021<o:p></o:p></span></b></p>

<p class=MsoNormalCxSpMiddle align=center style='text-align:center'><b
style='mso-bidi-font-weight:normal'><span style='font-size:14.0pt;font-family:
"Times New Roman",serif;color:#002060'>SUBHARUN MUKHERJEE <span
style='mso-tab-count:4'>                              </span>1NH13EE059<o:p></o:p></span></b></p>

<p class=MsoNormalCxSpMiddle align=center style='text-align:center'><b
style='mso-bidi-font-weight:normal'><span style='font-size:14.0pt;font-family:
"Times New Roman",serif;color:#002060'>SWETHA D <span style='mso-tab-count:
6'>                                                        </span>1NH13EE063<o:p></o:p></span></b></p>

<p class=MsoNormal align=center style='text-align:center'><b style='mso-bidi-font-weight:
normal'><span style='font-size:14.0pt;mso-bidi-font-size:13.0pt;font-family:
"Times New Roman",serif;color:#00B050'><o:p>&nbsp;</o:p></span></b></p>

<p class=MsoNormal align=center style='text-align:center'><b style='mso-bidi-font-weight:
normal'><span style='font-size:14.0pt;mso-bidi-font-size:13.0pt;font-family:
"Times New Roman",serif;color:#00B050'>2016-2017<o:p></o:p></span></b></p>

<p class=MsoNormal align=left style='text-align:left'><b style='mso-bidi-font-weight:
normal'><span style='font-size:16.0pt;mso-bidi-font-size:13.0pt;font-family:
"Times New Roman",serif'><o:p>&nbsp;</o:p></span></b></p>

<p class=MsoNormal align=left style='text-align:left'><b style='mso-bidi-font-weight:
normal'><span style='font-size:16.0pt;mso-bidi-font-size:13.0pt;font-family:
"Times New Roman",serif'>ABSTRACT<o:p></o:p></span></b></p>

<p class=MsoNormal><span style='font-size:14.0pt;mso-bidi-font-size:13.0pt;
font-family:"Times New Roman",serif'>Electrical performance analysis includes
crucial for advancement of any system in future to the necessary practical
level. This project is carried out with an objective to carry out performance
analysis of some electrical devices like transformer, motor, generator in terms
of its speed, temperature, voltage and current the parameters of respective
device is recorded using dedicated sensors deployed across the project module.
The project module includes the runtime java application along with Arduino
interface environment which automatically detects the faults across the
electrical devices and classifies it with the fault details. Based on the
specifications of the devices, the pre set value for sensors is modified using
Java and Arduino interface such that it automatically detects basic faults.
Moreover, analysis of continuous data collected in periodic intervals from
several motors helps in improvising them to the latest industrial demand.<o:p></o:p></span></p>

</div>

<!-- From Word Upto Here -->
</div>
 </div>
      <script type="text/javascript" src="https://code.jquery.com/jquery-2.1.1.min.js"></script>
      <script src="https://cdnjs.cloudflare.com/ajax/libs/materialize/0.98.2/js/materialize.min.js"></script>
      <script>$(".button-collapse").sideNav();  $(document).ready(function(){
    $('ul.tabs').tabs();
  });</script>
   </body>
</html>