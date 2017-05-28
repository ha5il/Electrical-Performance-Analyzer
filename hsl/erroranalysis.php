<?php
include ($_SERVER['DOCUMENT_ROOT'] . '/project/hsl/data.php');

function analysePerformance ($dataCode)
{
$eachCode  = array_map('intval', str_split($dataCode));

if ($eachCode[0] == 1) echo ('<br> The motor might be running at colder environment, better performance will be seen once motor heats up.');
else if ($eachCode[0] == 2) echo ('<br> The motor got overheat at this moment, please use better cooling system.');

if ($eachCode[1] == 1) echo ('<br>There is dip in supply voltage, please use voltage booster unit.');
else if ($eachCode[1] == 3) echo ('<br>The supply is higher than permitted limit, please use a stablizer.');

if ($eachCode[2] == 3 && $eachCode[3] == 1) echo ('<br>We found high current with low speed, probably due to overload or insufficient lubricant.');

echo ('<br><br>');
}

?>