<?php

//Declare standard parameters here
$temperature = 30;
$voltage = 1.5;
$current = 500;
$speed = 900;

// Specify maximum limit
$temperature_max = 45;
$voltage_max = 1.7;
$current_max = 600;
$speed_max = 1000;

// Specify minimum limit
$temperature_min = 25;
$voltage_min = 1.2;
$current_min = 100;
$speed_min = 800;

























//			IF TOLERANCE IS IN PERCENTAGE

/*
//Specify tolerance percentage
$temperature_tol = 10;
$voltage_tol = 10;
$current_tol = 10;
$speed_tol = 10;

// Calculating the maximum values as per tolerance value
$temperature_max = (1 + $temperature_tol / 100) * $temperature;
$voltage_max = (1 + $voltage_tol / 100) * $voltage;
$current_max = (1 + $current_tol / 100) * $current;
$speed_max = (1 + $speed_tol / 100) * $speed;

// Calculating the minimum values as per tolerance value
$temperature_min = (1 - $temperature_tol / 100) * $temperature;
$voltage_min = (1 - $voltage_tol / 100) * $voltage;
$current_min = (1 - $current_tol / 100) * $current;
$speed_min = (1 - $speed_tol / 100) * $speed;

*/
?>