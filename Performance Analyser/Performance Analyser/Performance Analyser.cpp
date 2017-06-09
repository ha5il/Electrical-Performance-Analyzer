#include "stdafx.h"
#include <iostream>
#include "csv.h"
#include <iomanip>
#include "ConsoleColor.h"

using namespace std;
long long int all_error_time[1000];		// these two array contains
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

float csv_tmax;
float csv_tmin;
float csv_vmax;
float csv_vmin;
float csv_cmax;
float csv_cmin;
float csv_smax;
float csv_smin;

void updateScreen(std::string);
void getStandardPara(void);
void getCSV_max_min(void);
int single_error_code(float, float, float);
void errorCodeClubber(long long int, int, int, int, int);
void generate_brief_report(void);
std::string analysePerformance(int);
void printTimeStamp(long long int);
std::string tomonth(int);
void printAll_Fluctuations(void);

int main()
{
	updateScreen("Welcome");
	std::cout << endl << "Please drag and drop the error free DATA.CSV here: ";
	std::cin >> path_to_file;
	updateScreen("Welcome");

	getCSV_max_min();
	// Do Main calculation
	io::CSVReader<5> in(path_to_file);
	in.read_header(io::ignore_extra_column, "Time", "Temperature", "Voltage", "Current", "Speed");
	long long int time_csv;
	float temperature_csv;
	float voltage_csv;
	float current_csv;
	float speed_csv;
	updateScreen("Welcome");
	getStandardPara();				//it fetches Form data as in php
	updateScreen("Welcome");
	updateScreen("GettingErrorCode");
	while (in.read_row(time_csv, temperature_csv, voltage_csv, current_csv, speed_csv))
	{
		// get error codes
		temperature_error = single_error_code(temperature_csv, temperature_maximum, temperature_minimum);
		voltage_error = single_error_code(voltage_csv, voltage_maximum, voltage_minimum);
		current_error = single_error_code(current_csv, current_maximum, current_minimum);
		speed_error = single_error_code(speed_csv, speed_maximum, speed_minimum);
		// verify and store error codes
		errorCodeClubber(time_csv, temperature_error, voltage_error, current_error, speed_error);
	}
	updateScreen("Welcome");
	std::cout << endl << "I found " << yellow << no_error_count << white << " data inside the limits you gave me and " << red << error_count << white << " fluctuated." << endl;

	if (error_count > 0)
	{
		generate_brief_report();
		printAll_Fluctuations();
	}
	std::cout << endl << endl << endl << endl << endl << endl << endl << endl << green << setfill('-') << setw(25) << "-" << "End of Program" << setfill('-') << setw(25) << "-" << white << endl;
	std::cout << "Press any key and hit Enter twice to exit...";
	int any_key_to_exit;
	std::cin >> any_key_to_exit;
	return 0;
}

void getCSV_max_min(void)
{
	io::CSVReader<5> inn(path_to_file);
	inn.read_header(io::ignore_extra_column, "Time", "Temperature", "Voltage", "Current", "Speed");
	long long int time;
	float temperature;
	float voltage;
	float current;
	float speed;
	int one_time_count = 0;

	updateScreen("Welcome");
	updateScreen("GettingCSV_max_min");
	while (inn.read_row(time, temperature, voltage, current, speed))
	{
		if (one_time_count == 0)
		{
			csv_tmax = csv_tmin = temperature;
			csv_vmax = csv_vmin = voltage;
			csv_cmax = csv_cmin = current;
			csv_smax = csv_smin = speed;
			one_time_count++;
		}
		else
		{
			if (temperature > csv_tmax) csv_tmax = temperature;
			else if (temperature < csv_tmin) csv_tmin = temperature;
			if (voltage > csv_vmax) csv_vmax = voltage;
			else if (voltage < csv_vmin) csv_vmin = voltage;
			if (current > csv_cmax) csv_cmax = current;
			else if (current < csv_cmin) csv_cmin = current;
			if (speed > csv_smax) csv_smax = speed;
			else if (speed < csv_smin) csv_smin = speed;
		}
	}
}
void getStandardPara(void)
{
	float temp_swap;
	std::cout << endl << "What are the maximum and minimum limits I should check for?\n(Bracket values are Maximum and Minimum value in CSV file)" << endl << endl;
	std::cout << setw(25) << left << "Maximum Temperature" << "(" << csv_tmax << ")" << ": ";
	std::cin >> temperature_maximum;
	std::cout << setw(25) << "Minimum Temperature" << "(" << csv_tmin << ")" << ": ";
	std::cin >> temperature_minimum;
	if (temperature_maximum < temperature_minimum)
	{
		temp_swap = temperature_maximum;
		temperature_maximum = temperature_minimum;
		temperature_minimum = temp_swap;
		cout << blue << "I found value of Max Temperature greater than Min Temperature, so I swapped them..." << white << endl;
	}
	std::cout << endl << setw(25) << left << "Maximum Voltage" << "(" << csv_vmax << ")" << ": ";
	std::cin >> voltage_maximum;
	std::cout << setw(25) << left << "Minimum Voltage" << "(" << csv_vmin << ")" << ": ";
	std::cin >> voltage_minimum;
	if (voltage_maximum < voltage_minimum)
	{
		temp_swap = voltage_maximum;
		voltage_maximum = voltage_minimum;
		voltage_minimum = temp_swap;
		cout << blue << "I found value of Max Voltage greater than Min Voltage, so I swapped them..." << white << endl;
	}
	std::cout << endl << setw(25) << left << "Maximum Current" << "(" << csv_cmax << ")" << ": ";
	std::cin >> current_maximum;
	std::cout << setw(25) << left << "Minimum Current" << "(" << csv_cmin << ")" << ": ";
	std::cin >> current_minimum;
	if (current_maximum < current_minimum)
	{
		temp_swap = current_maximum;
		current_maximum = current_minimum;
		current_minimum = temp_swap;
		cout << blue << "I found value of Max Minimum greater than Min Minimum, so I swapped them..." << white << endl;
	}
	std::cout << endl << setw(25) << left << "Maximum Speed" << "(" << csv_smax << ")" << ": ";
	std::cin >> speed_maximum;
	std::cout << setw(25) << left << "Minimum Speed" << "(" << csv_smin << ")" << ": ";
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
		std::cout << endl << "Could you please wait until I read the CSV file and generate report...";
	}

	else if (region == "GettingCSV_max_min")
	{
		std::cout << endl << "I am searching for maximum and minimum values in the CSV file...";
	}
}

void errorCodeClubber(long long int timeStamp, int t, int v, int c, int s)
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
	int last_error_code = 2222;			// 2222 isn't error, in such case this function will never be called

	for (int i = 1; i <= error_count; i++)
	{
		if (all_error_codes[i] == last_error_code) continue;
		printTimeStamp(all_error_time[i]);
		std::cout << analysePerformance(all_error_codes[i]);
		last_error_code = all_error_codes[i];
	}
}

void printTimeStamp(long long int raw)
{
	//Formmatting date and time
	int seconds = raw % 100;
	raw = raw / 100;
	int minutes = raw % 100;
	raw = raw / 100;
	int hours = raw % 100;
	raw = raw / 100;
	int date = raw % 100;
	raw = raw / 100;
	int month = raw % 100;
	raw = raw / 100;
	cout << endl << blue << date << tomonth(month) << raw << " at " << hours << ":" << minutes << ":" << seconds << white;
}

std::string tomonth(int mnth)
{
	if (mnth == 1) return " January ";
	else if (mnth == 2) return " February ";
	else if (mnth == 3) return " March ";
	else if (mnth == 4) return " April ";
	else if (mnth == 5) return " May ";
	else if (mnth == 6) return " June ";
	else if (mnth == 7) return " July ";
	else if (mnth == 8) return " August ";
	else if (mnth == 9) return " September ";
	else if (mnth == 10) return " Octuber ";
	else if (mnth == 11) return " November ";
	else if (mnth == 12) return " December ";
	else return " Something fissy! ";
}

void printAll_Fluctuations(void)
{
	std::cout << endl << yellow << "Below are all the fluctuations I found during analysis" << endl << "Error code is order of Temperature, Voltage, Current and speed\nwhere,\n3 is HIGH\n2 is NORMAL\n1 is LOW\n0 is OFF" << white << endl;
	std::cout << "---------------------------------------------" << endl;
	std::cout << "| Error Code |           Timestamp          |" << endl;
	std::cout << "---------------------------------------------" << endl;

	for (int i = 1; i <= error_count; i++)
	{
		std::cout << "|    " << setw(8) << left << all_error_codes[i] << setw(5) << "|        " << all_error_time[i] << "        |" << endl;
	}
	std::cout << "---------------------------------------------" << endl;
}

std::string analysePerformance(int dataCode)
{
	std::string result = "\n";
	int eachCode_s = dataCode % 10;
	dataCode = dataCode / 10;
	int eachCode_c = dataCode % 10;
	dataCode = dataCode / 10;
	int eachCode_v = dataCode % 10;
	dataCode = dataCode / 10;
	int eachCode_t = dataCode;

	// Check if supply is given?
	if (eachCode_v == 0) result = result + "Motor is turned off. We didnot find any supply voltage.\n";
	else
	{
		// Checking Temperature
		if (eachCode_t == 1) result = result + "The motor might be running in a colder environment, better performance will be seen once it heats up.\n";
		else if (eachCode_t == 3) result = result + "The motor got overheat at this moment, please use a better cooling system.\n";

		// Checking Voltage
		if (eachCode_v == 1) result = result + "There is a dip in supply voltage, please use voltage booster unit.\n";
		else if (eachCode_v == 3) result = result + "The supply is higher than permitted limit, please use a stabilizer.\n";

		// Checking Current and Speed
		if (eachCode_c == 3 && eachCode_s == 1) result = result + "We found high current with low speed, probably due to overload or insufficient lubricant.\n";
		else if (eachCode_c == 3 && eachCode_s == 0) result = result + "We found high current with zero speed due to blocked rotor.\n";
	}
	return result;
}