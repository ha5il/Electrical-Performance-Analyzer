#include "stdafx.h"
#include <iostream>
#include "csv.h"

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

void updateScreen(std::string);
void getStandardPara(void);
int single_error_code(float, float, float);
void errorCodeClubber(std::string, int, int, int, int);

int main()
{
	updateScreen("Welcome");
	std::cout << "\nPlease drag and drop the DATA.CSV here from SD card: ";
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
	}

	//Analuse clubbed error codes here by creating a function
	
	std::cout << "\n\n\n\n\n\n\n\n--------------------------End of Program--------------------------";
	std::cout << "\nPress any key and hit Enter to exit...";
	int any_key_to_exit;
	std::cin >> any_key_to_exit;
    return 0;
}

void getStandardPara(void) {
	float temp_swap;
	std::cout << "\nPlease enter the maximum and minimum limits";
	std::cout << "\n\nMaximum Temperature  : ";
	std::cin >> temperature_maximum;
	std::cout << "Minimum Temperature  : ";
	std::cin >> temperature_minimum;
	if (temperature_maximum < temperature_minimum)
	{
		temp_swap = temperature_maximum;
		temperature_maximum = temperature_minimum;
		temperature_minimum = temp_swap;
		cout << "I found value of Max Temperature greater than Min Temperature, so I swapped them...\n";
	}
	std::cout << "\nMaximum Voltage      : ";
	std::cin >> voltage_maximum;
	std::cout << "Minimum Voltage      : ";
	std::cin >> voltage_minimum;
	if (voltage_maximum < voltage_minimum)
	{
		temp_swap = voltage_maximum;
		voltage_maximum = voltage_minimum;
		voltage_minimum = temp_swap;
		cout << "I found value of Max Voltage greater than Min Voltage, so I swapped them...\n";
	}
	std::cout << "\nMaximum Current      : ";
	std::cin >> current_maximum;
	std::cout << "Minimum Current      : ";
	std::cin >> current_minimum;
	if (current_maximum < current_minimum)
	{
		temp_swap = current_maximum;
		current_maximum = current_minimum;
		current_minimum = temp_swap;
		cout << "I found value of Max Minimum greater than Min Minimum, so I swapped them...\n";
	}
	std::cout << "\nMaximum Speed        : ";
	std::cin >> speed_maximum;
	std::cout << "Minimum Speed        : ";
	std::cin >> speed_minimum;
	if (speed_maximum < speed_minimum)
	{
		temp_swap = speed_maximum;
		speed_maximum = speed_minimum;
		speed_minimum = temp_swap;
		cout << "I found value of Max Speed greater than Min Speed, so I swapped them...\n";
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
		std::cout << "\t\t\t\t\t\tElectrical Performance Analyser\n";
	}

	else if (region == "GettingErrorCode")
	{
		std::cout << "I am busy on reading csv file and generating error codes...";

	}
	else if (region == "Analysing")
	{
		std::cout << "Please wait while I analyse and present report...";
	}

}

void errorCodeClubber(std::string timeStamp, int t, int v, int c, int s) {
	if (t != 2 && v != 2 && c != 2 && s != 2)
	{
		error_count++;
		all_error_time [error_count] = timeStamp;
		all_error_codes[error_count] = t * 1000 + v * 100 + c * 10 + s;		//Future bug, in case t gets 0... ONLY t
	}
}