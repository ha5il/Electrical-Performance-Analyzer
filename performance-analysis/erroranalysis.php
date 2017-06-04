<?php

/*
	$eachCode[0] --> Temperature				3 --> High
	$eachCode[1] --> Voltage 					2 --> Normal
	$eachCode[2] --> Couuent					1 --> Low
	$eachCode[3] --> Speed
*/

function analysePerformance($dataCode)
{
	$eachCode = array_map('intval', str_split($dataCode));
	
	// Checking Temperature
	if ($eachCode[0] == 1) echo ('<br /> The motor might be running at colder environment, better performance will be seen once motor heats up.');
	else if ($eachCode[0] == 3) echo ('<br /> The motor got overheat at this moment, please use better cooling system.');
	
	// Checking Voltage
	if ($eachCode[1] == 1) echo ('<br />There is dip in supply voltage, please use voltage booster unit.');
	else if ($eachCode[1] == 3) echo ('<br />The supply is higher than permitted limit, please use a stabilizer.');
	
	// Checking Current and Speed
	if ($eachCode[2] == 3 && $eachCode[3] == 1) echo ('<br />We found high current with low speed, probably due to overload or insufficient lubricant.');
	
	echo ('<br /><br />');
}

?>