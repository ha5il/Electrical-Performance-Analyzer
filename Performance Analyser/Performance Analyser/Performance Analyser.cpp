#include "stdafx.h"
#include <iostream>
#include "csv.h"
#include <iomanip>
#include "ConsoleColor.h"

using namespace std;
std::string all_error_time[1000];		// these two array contains
int all_error_codes[1000];				// error code and time of occurance

std::string path_to_file;
float temperature_maximum;
float temperature_minimum;
float voltage_maximum;
float voltage_minimum;
float current_maximum;
float current_minimum;
float speed_maximum;
float speed_minimum;
int temperature_error;
int voltage_error;
int current_error;
int speed_error;
int error_count = 0;
int no_error_count = 0;

void updateScreen(std::string);
void getStandardPara(void);
int single_error_code(float, float, float);
void errorCodeClubber(std::string, int, int, int, int);
void generate_brief_report(void);
std::string analysePerformance(int);
std::string toString(std::string);

int main()
{
	updateScreen("Welcome");
/*	std::cout << endl << "Please drag and drop the DATA.CSV here from SD card: ";
	std::cin >> path_to_file;
	updateScreen("Welcome");
	getStandardPara();				//it fetches Form data as in php
	updateScreen("Welcome");
	
	io::CSVReader<5> in(path_to_file);
	in.read_header(io::ignore_extra_column, "Time", "Temperature", "Voltage", "Current", "Speed");
	std::string time_csv;
	float temperature_csv;
	float voltage_csv;
	float current_csv;
	float speed_csv;
	while (in.read_row(time_csv, temperature_csv, voltage_csv, current_csv, speed_csv))
		{
		updateScreen("Welcome");
		updateScreen("GettingErrorCode");
		// get error codes
		temperature_error = single_error_code(temperature_csv, temperature_maximum, temperature_minimum);
		voltage_error = single_error_code(voltage_csv, voltage_maximum, voltage_minimum);
		current_error = single_error_code(current_csv, current_maximum, current_minimum);
		speed_error = single_error_code(speed_csv, speed_maximum, speed_minimum);
		// verify and store error codes
		errorCodeClubber(time_csv, temperature_error, voltage_error, current_error, speed_error);
	}*/

	errorCodeClubber("20170518124500", 2, 3, 2, 2);

	std::cout << endl << "I found " << yellow << no_error_count << white << " clear data and " << red << error_count << white << " total fluctutions as per the limits you gave me." << endl;
	
	if (error_count > 0)
	{
		generate_brief_report();

	}



	//---------------------------------------------------------------------------------------------------------------------------

	std::cout << endl << endl << endl << endl << endl << endl << endl << endl << green << setfill('-') << setw(25) << "-" << "End of Program" << setfill('-') << setw(25) << "-" << white << endl;
	std::cout << "Press any key and hit Enter to exit...";
	int any_key_to_exit;
	std::cin >> any_key_to_exit;
    return 0;
}

void getStandardPara(void) {
	float temp_swap;
	std::cout << endl << "Please enter the maximum and minimum limits" << endl << endl;
	std::cout << setw(35) << left << "Maximum Temperature" << "-->    ";
	std::cin >> temperature_maximum;
	std::cout << setw(35) << "Minimum Temperature" << "-->    ";
	std::cin >> temperature_minimum;
	if (temperature_maximum < temperature_minimum)
	{
		temp_swap = temperature_maximum;
		temperature_maximum = temperature_minimum;
		temperature_minimum = temp_swap;
		cout << blue << "I found value of Max Temperature greater than Min Temperature, so I swapped them..." << white << endl;
	}
	std::cout << endl << setw(35) << left << "Maximum Voltage" << "-->    ";
	std::cin >> voltage_maximum;
	std::cout << setw(35) << left << "Minimum Voltage" << "-->    ";
	std::cin >> voltage_minimum;
	if (voltage_maximum < voltage_minimum)
	{
		temp_swap = voltage_maximum;
		voltage_maximum = voltage_minimum;
		voltage_minimum = temp_swap;
		cout << blue << "I found value of Max Voltage greater than Min Voltage, so I swapped them..." << white << endl;
	}
	std::cout << endl << setw(35) << left << "Maximum Current" << "-->    ";
	std::cin >> current_maximum;
	std::cout << setw(35) << left << "Minimum Current" << "-->    ";
	std::cin >> current_minimum;
	if (current_maximum < current_minimum)
	{
		temp_swap = current_maximum;
		current_maximum = current_minimum;
		current_minimum = temp_swap;
		cout << blue << "I found value of Max Minimum greater than Min Minimum, so I swapped them..." << white << endl;
	}
	std::cout << endl << setw(35) << left << "Maximum Speed" << "-->    ";
	std::cin >> speed_maximum;
	std::cout << setw(35) << left << "Minimum Speed" << "-->    ";
	std::cin >> speed_minimum;
	if (speed_maximum < speed_minimum)
	{
		temp_swap = speed_maximum;
		speed_maximum = speed_minimum;
		speed_minimum = temp_swap;
		cout << blue << "I found value of Max Speed greater than Min Speed, so I swapped them..." << white << endl;
	}
}

int single_error_code(float analyser, float maxi, float mini)
{
	if (analyser == 0) return 0;
	else if (analyser > maxi) return 3;
	else if (analyser < mini) return 1;
	else return 2;
}

void updateScreen(std::string region)
{
	if (region == "Welcome")
	{
		system("CLS");
		std::cout << green << setw(45) << right << "Electrical Performance Analyser" << white << endl;
	}

	else if (region == "GettingErrorCode")
	{
		std::cout << endl << "I am busy on reading csv file and generating error codes...";

	}
	else if (region == "Analysing")
	{
		std::cout << "Please wait while I analyse and present report...";
	}

}

void errorCodeClubber(std::string timeStamp, int t, int v, int c, int s)
{
	if (t == 2 && v == 2 && c == 2 && s == 2)
	{
		no_error_count++;
	}
	else
	{
		error_count++;
		all_error_time[error_count] = timeStamp;
		all_error_codes[error_count] = t * 1000 + v * 100 + c * 10 + s;		//Future bug, in case t gets 0... ONLY t
	}
}

void generate_brief_report(void)
{
	int i;
	int last_error_code = 2222;			// 2222 isn't error, in such case this function will never be called
	for (i = 1; i <= error_count; i++)
	{
		if (all_error_codes[error_count] == last_error_code) continue;
		std::cout << endl << blue << toString(all_error_time[error_count]) << white << endl;
		std::cout << analysePerformance(all_error_codes[error_count]);
		last_error_code = all_error_codes[error_count];
	}
}

std::string toString(std::string raw)
{
	//Formmatting date and time
	std::string result;
	std::cout << endl << "Debug Start..." << endl;
	std::cout << "RAW Data is " << raw << endl;
	std::cout << "raw 1 and 2 are " << raw[1] << raw[2] << endl;
	result = raw[1] + raw[2];
	std::cout << "clubbed raw 1 and 2 is " << result << endl;

	

	std::cout << endl << "Debug End..." << endl;
	return result;
}


std::string analysePerformance(int dataCode)
{
	int eachCode_s = dataCode % 10;
	dataCode = dataCode / 10;
	int eachCode_c = dataCode % 10;
	dataCode = dataCode / 10;
	int eachCode_v = dataCode % 10;
	dataCode = dataCode / 10;
	int eachCode_t = dataCode;

	// Check if supply is given?
	if (eachCode_v == 0) return ("Motor is turned off. We didnot find any supply voltage.");
	else
	{
		// Checking Temperature
		if (eachCode_t == 1) return ("The motor might be running in a colder environment, better performance will be seen once it heats up.");
		else if (eachCode_t == 3) return ("The motor got overheat at this moment, please use a better cooling system.");

		// Checking Voltage
		if (eachCode_v == 1) return("There is a dip in supply voltage, please use voltage booster unit.");
		else if (eachCode_v == 3) return("The supply is higher than permitted limit, please use a stabilizer.");

		// Checking Current and Speed
		if (eachCode_c == 3 && eachCode_s == 1) return("We found high current with low speed, probably due to overload or insufficient lubricant.");
		else if (eachCode_c == 3 && eachCode_s == 0) return("We found high current with zero speed due to blocked rotor.");
	}
}