//
//	Name:		Beauchamp, Joshua
//	Project:	2
//	Due:		02-25-2025
//	Course:		cs-2560-01-sp25
//	Description:
//			The program is desgined to take user input for the month and year of their choosing.
//			Using functions called getDaysInMonth and getDayOfTheWeek, the program computes
//			values such as the day the month starts on and how many total days there are in the month.
//			Following the functions' executions, the function printCalendar then formats the calendar
//			properly and then outputs it into a file for the user, naming it after the month and year
//			that was inputted.
//

#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>

using namespace std;

// Using switch cases, returns the total amount of days of the given month.
// It takes into account the days for leap years by checking if the year is
// divisble by 4 and not by 100 or divisible by 400.
int getDaysInMonth (int month, int year)
{
	switch (month) {
	case 4: case 6: case 9: case 11:
		return 30;
		break;
	case 2:
		return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) ? 29 : 28;	//Checks for leap year
		break;
	default:
		return 31;
		break;
	}
}	//End getDaysInMonth

// Computes the day that the week starts on, i.e. 0 for Sunday, 1 for Monday, etc.
int getDayOfTheWeek (int day, int month, int year)
{
	int a, y, m, dow;

	a = (14 - month) / 12;
	y = year - a;
	m = month + (12 * a) - 2;

	return (day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
}	//End getDayOfTheWeek

// Formats and outputs the calendar properly for writing to a file
void printCalendar(int daysInMonth, int dayOfWeek, int month, int year)
{
	string filename;
	ofstream outputFile;

	filename = to_string(month) + "-" + to_string(year) + ".txt";	//Creates the file name for outputting based on the month and year

	outputFile.open(filename);		//Opens or creates the file for outputting
	cout << filename << " output generated." << endl;

	outputFile << month << "/" << year << endl;
	outputFile << "Sun  Mon  Tue  Wed  Thu  Fri  Sat" << endl;
	outputFile << "---------------------------------" << endl;

	int dayCounter = 0;		//tracks how many days the for loops have iterated through so that a newline is entered for the new week

	// Loops until it reaches the first day of the month
	for(int i = 0; i < dayOfWeek; i ++){
		if(i % 7 == 0){
			outputFile << setw(3) <<  " ";		// White space for beginning of the week
		}
		else{
			outputFile << setw(5) <<" ";	// White space for any day that is not Sunday
		}
		dayCounter++;
	}

	// Outputs the days and starts a newline when a week is completed
	for(int i = 1; i <= daysInMonth; i++){
		if(dayCounter % 7 == 0){
			outputFile << endl << setw(3) << i;	// Checks if current day is Sunday, making a newline for the new week
		}
		else {
			outputFile << setw(5) << i;
		}
		dayCounter++;
	}

	outputFile.close();		//Closes output file
}	//End printCalendar

// Prompts the user to enter a month and year to compute the gregorian calendar for that year.
// Calls functions getDaysInMotnh and getDayOfTheWeek to help in the computation and logic.
// After computing, the calendar is then outputted into a text file where it is named after the
// the month and year that the user inputted.
int main()
{
	int month, year;
	int const day = 1;

	//Prompts user to input month and year and reads it into the varaibles month and year for computing
	cout << "Monthly Calendar by J. Beauchamp" << endl << endl;
	cout << "Enter month year? ";

	cin >> month >> year;

	int daysInMonth = getDaysInMonth(month, year);
	int dayOfWeek = getDayOfTheWeek(day, month, year);

	printCalendar(daysInMonth, dayOfWeek, month, year);

	return 0;
}	//End main