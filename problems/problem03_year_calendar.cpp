/*
===============================================================================
Problem: Full Year Calendar Generator
===============================================================================

Goal
----
Create a C++ program that generates and displays a formatted calendar
for all 12 months of a given year.

Requirements
------------
- Handle all months (Jan–Dec)
- Correctly detect leap years
- Each month should be formatted with weekdays aligned

Concepts Practiced
------------------
- Divide and conquer (splitting program into small functions)
- Function design and reuse
- Leap year calculation
- Gregorian calendar weekday calculation
- Output formatting using i/o manipulators (setw, alignment)
- Loops and iteration

Program Flow
------------
1. Read the year from the user.
2. Print a year header.
3. Loop through all 12 months:
    a. Print month header
    b. Print all weekdays
    c. Print all days of the month, aligned correctly

Functions / Procedures
----------------------
ReadYear()          -> Read year from user
IsLeapYear()        -> Returns true if year is leap
MonthName()         -> Returns month name from index
DayOfWeekOrder()    -> Calculate weekday of given date
DayName()           -> Returns weekday name
CalculateDaysInMonth() -> Returns number of days in month
PrintMonthDays()    -> Prints all days of a month
MonthCalendar()     -> Prints month header + days
YearCalendar()      -> Prints full calendar for the year

Example Input
-------------
Year: 2024

Example Output
--------------
______________________________

        Calendar 2024
______________________________

_______________Jan_______________
Sun  Mon  Tue  Wed  Thur Fri  Sat
      1    2    3    4    5
6    7    8    9    10   11   12
...
_______________Dec_______________
Sun  Mon  Tue  Wed  Thur Fri  Sat
1    2    3    4    5    6    7
...
===============================================================================
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

//function to read year
short ReadYear() {
	short year = 0;
	cout << "Please enter a year: " << endl;
	cin >> year;
	return year;
}


//function to check if the year is leap year
bool IsLeapYear(short year) {
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}


//
string MonthName(short month) {
	string monthNames[12] = { "Jan", "Feb", "Mar", "April", "May", "June", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
	return monthNames[month - 1];
}

//function to calculate day based on Gregorian calendar
short DayOfWeekOrder(short year, short month, short day) {
	short a = (14 - month) / 12;
	short y = year - a;
	short m = month + (12 * a - 2);
	short d = (day + y + (y / 4) - (y / 100) + (y / 400) + (31 * m / 12)) % 7;
	return d;
}

string DayName(short dayOfWeekOrder) {
	string dayNames[7] = { "Sun", "Mon", "Tue", "Wed", "Thur", "Fri", "Sat" };
	return dayNames[dayOfWeekOrder];
}


//function to calculate the days in month
short CalculateDaysInMonth(short month, short year) {
	return (month == 2) ? (IsLeapYear(year) ? 29 : 28)
		: (month == 4 || month == 6 || month == 9 || month == 11) ? 30
		: 31;
}


//preocedure to print the days of a given month
void PrintMonthDays(short month, short year) {
	short numberOfDaysInMonth = CalculateDaysInMonth(month, year);

	//print all day names as first line
	for (short i = 0; i < 7; i++) {
		cout << left << setw(5) << DayName(i);
	}
	printf("\n");

	// Index of the day from 0 to 6
	short dayOfWeekOrder = DayOfWeekOrder(year, month, 1);  // use it to know the beginning of the days fro sun to sat

	// Print appropriate spaces
	for (short i = 0; i < dayOfWeekOrder; i++) {
		printf("     ");
	}
	//cout << setw(3) << 1; // print the first day of the month
	for (short j = 1; j <= numberOfDaysInMonth; j++) {
		dayOfWeekOrder++;
		cout << left << setw(5) << j;
		//printf("%5d", j);
		if (dayOfWeekOrder == 7) {
			dayOfWeekOrder = 0;
			printf("\n");
		}
	}
}

// preocedure to prints the month header and the days of the given month and year
void MonthCalendar(short month, short year) {
	cout << "_______________" << MonthName(month) << "_______________" << endl;
	PrintMonthDays(month, year);
}

// preocedure to prints the year header and the months of the given year
void YearCalendar(short year) {
	cout << "______________________________\n\n";
	cout << "\tCalendar " << year << endl;
	cout << "______________________________\n\n";

	for (short i = 0; i < 12; i++) {
		MonthCalendar(i+1, year);
		cout << endl;
		cout << endl;
	}
}

// Entry point of program
int main()
{
	short year = ReadYear();
	YearCalendar(year);
	return 0;
}