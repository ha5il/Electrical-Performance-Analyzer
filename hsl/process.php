<?php

/*
if $skipCount > 0, then some rows have to be skipped
the rows to skip are on array $skippedRow[]

Number of fluctuations from standard values as specified on data.php --> $errorCount
List of error codes are on array $errors[]
Row number of error is on array $errorRow[]

Eg.
If error is on row 4,
Fetch the error code as $errors[4]
The individual senssed parameters can be fetched as $t[4]...
*/

$errors[0] = 0;                // To avoide array offset error and is useless

   if ($errorCount > 0)
  {
	  echo ("<br>Error Codes are:");
	  
	  for ($i=1;$i<=$errorCount;$i++)
	  {
		  if ($errors[$i] == $errors [$i-1])
		  continue;
	  
	  /* Now analyse the error, continue above skips the same adjacent error code
	  
	     Error codes starts from row 2
         temperature --> $t[row]			Error Code Description
         voltage     --> $v[row]			3 --> High
         current     --> $c[row]			2 --> Normal
         speed       --> $s[row]			1 --> Low
		 
	  */
	  
	  
	  echo ("<br>" . $errors[$i]);
	  
	  }
	  
	  
	  
	  /*
	  TO CHECK REPEATED ADJACENT ERROR
	  for ($i=1; $i<=$errorCount; $i++)
	  {
		// checking if same error code exists on adjacent rows
		for ($j=1; $j<=$j+1; $i++)
		{
			$errorCode[$errorRow[]]
		}
		  
	  }*/ 
	  
	  
	  
	   // Summary about fluctuations
	   echo ("<br><center>|---------------- Summary about fluctuations ----------------|");
	 echo ("<br><br>We found some fluctuations!<br>");
	 echo ("<br>No. of fluctuations = " . $errorCount);
	 echo ("<br>Rows containing fluctuated data is listed below<br><br>");
	 for ($i=1; $i<=$errorCount; $i++)
	 {
	 echo ($errorRow[$i] . "<br>");
	 }
	 echo ("<center>");
 }
 else echo ("<br>We didn't find any fluctuation from standard values as specified on data.php");

 // Summary about skipped data
  if ($skipCount > 0)
  {
	   echo ("<br><center>|--------------------- Summary about skips ---------------------|");
	 echo ("<br><br>Some rows of CSV file contains extra/unsufficient value!");
	 echo ("<br>No. of skipped data = " . $skipCount);
	 echo ("<br>Rows that were skipped while processing is listed below<br><br>");
	 for ($i=1; $i<=$skipCount; $i++)
	 {
	 echo ($skippedRow[$i] . "<br>");
	 }
	 echo ("<center>");
 }
 ?>