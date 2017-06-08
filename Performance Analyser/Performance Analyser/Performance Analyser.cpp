#include "stdafx.h"
#include <iostream>

char temp;					//Be sure it's used just after taking input
int any_key_to_exit;

void initialize_csv(void);
int main()
{
	std::cout << "\t\t\t\t\t\tElectrical Performance Analyser";
	initialize_csv();

	std::cout << "\n\n\n\n\n\n\n\n--------------------------End of Program--------------------------";
	std::cout << "\nPress any key and Enter to exit...";
	std::cin >> any_key_to_exit;
    return 0;
}

void initialize_csv(void)
{
	std::cout << "\n\nShall I use Standard DATA.CSV? (Y/N): ";
	std::cin >> temp;
	if (temp == 'Y' || temp == 'y')
	{
		std::cout << "Using standard csv file...";

	}
	else if (temp == 'N' || temp == 'n')
	{
		std::cout << "Sorry :( only standard csv is currently available.";
		initialize_csv();
	}
	else
	{
		std::cout << "I couldn't understand, please enter either Y or y or N or n";
		initialize_csv();
	}
}