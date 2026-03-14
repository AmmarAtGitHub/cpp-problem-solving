/*
===============================================================================
Problem: Monthly Calendar Generator
===============================================================================

Goal
----
Create a C++ program that generates and displays a formatted calendar
for a given month and year.

Requirements
------------
- Handle all 12 months
- Correctly detect leap years
- February must have 29 days during leap years

Concepts Practiced
------------------
- Divide and conquer
- Function design
- Leap year logic
- Gregorian calendar calculation
- Output formatting

Program Flow
------------
1. Read a year from the user
2. Read a month from the user
3. Determine leap year
4. Calculate days in month
5. Determine starting weekday
6. Print formatted calendar

Example Input
-------------
Year  : 2000
Month : 4

Example Output
--------------

_______________April_______________
Sun  Mon  Tue  Wed Thur  Fri  Sat
                              1
2    3    4    5    6    7    8
9    10   11   12   13   14   15
16   17   18   19   20   21   22
23   24   25   26   27   28   29
30

===============================================================================
*/


#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

//divide and conquer: Requirements
//function to read year
//function to read month
//function to return month name
//function to check if the year is leap year


//function to read year
short ReadYear() {
	short year = 0;
	cout << "Please enter a year: " << endl;
	cin >> year;
	return year;
}

//function to read month
short ReadMonth() {
	short month = 0;
	cout << "Please enter a month: " << endl;
	cin >> month;
	return month;
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


//function to calculate the days of a month e.g. 28/29 for leap years or 31/30 for the rest
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
		cout <<  DayName(i) << setw(5);
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



//procedure to prin the month header and the days of the given month and year
void MonthTable(short month, short year) {
	cout << "_______________" << MonthName(month) << "_______________" << endl;
	PrintMonthDays(month, year);
}



// Entry point of program
int main()
{
	short year = ReadYear();
	short month = ReadMonth();
	MonthTable(month, year);
	return 0;
}
