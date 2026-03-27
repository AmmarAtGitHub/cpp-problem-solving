/*
===============================================================================
Problem: Calculate Age in Days
===============================================================================

Goal
----
Create a program that calculates a person's age in days based on their
date of birth and the current system date.

Requirements
------------
- Read a full birth date (day, month, year)
- Get the current system date automatically
- Correctly handle leap years
- Accurately calculate the number of days between two dates

Concepts Practiced
------------------
- Structs (custom data types)
- Divide and conquer (breaking problem into functions)
- Date comparison logic
- Leap year calculation
- Iterative date increment
- Working with system date (time library)

Program Flow
------------
1. Read the user's birth date.
2. Get the current system date.
3. Compare the two dates.
4. Increment the earlier date day by day.
5. Count total days between the two dates.
6. Display the result.

Functions
---------
ReadFullDate()           -> Reads full date from user
isLeapYear()             -> Checks if year is leap
NumberOfDaysInAMonth()   -> Returns days in a month
IsDate1BeforeDate2()     -> Compares two dates
IncreaseDateByOneDay()   -> Moves date forward by one day
GetDifferenceInDays()    -> Calculates total days difference
GetSystemDate()          -> Retrieves current system date

Example
-------
Input:
Date of Birth:
Day: 1
Month: 1
Year: 2000

Output:
Your age in days is: 9500 (example)

===============================================================================
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#pragma warning(disable : 4996)

using namespace std;

//structure to hold the date
struct stDate {
	short Year;
	short Month;
	short Day;
};

//function to read day
short ReadDay() {
	short Day;
	cout << "\nPlease enter a Day? ";
	cin >> Day;
	return Day;
}
//function to read month
short ReadMonth() {
	short Month;
	cout << "\nPlease enter a Month? ";
	cin >> Month;
	return Month;
}
//function to read year
short ReadYear() {
	short Year;
	cout << "\nPlease enter a Year? ";
	cin >> Year;
	return Year;
}

//function to read full date
stDate ReadFullDate() {
	stDate Date;
	Date.Day = ReadDay();
	Date.Month = ReadMonth();
	Date.Year = ReadYear();
	return Date;
}

//function to check if the year is leap year
bool isLeapYear(short Year) {
	return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
}

//function to calculate the number of days in month 30, 31,28,or 29(leap year)
short NumberOfDaysInAMonth(short Month, short Year) {
	if (Month < 1 || Month>12)
		return 0;
	int days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	return (Month == 2) ? (isLeapYear(Year) ? 29 : 28) :
		days[Month - 1];
}


//function to calculate the number of days from beginning to a certain day
short CalculateDaysInYear(stDate date) {
	short totalDays = 0;
	for (short i = 1; i < date.Month; i++) {
		totalDays += NumberOfDaysInAMonth(i, date.Year);
	}

	totalDays += date.Day;
	return totalDays;
}

//function to compare two dates and return true if date1 is before date2
bool IsDate1BeforeDate2(stDate Date1, stDate Date2)
{
	return (Date1.Year < Date2.Year) ? true : ((Date1.Year ==
		Date2.Year) ? (Date1.Month < Date2.Month ? true : (Date1.Month ==
			Date2.Month ? Date1.Day < Date2.Day : false)) : false);
}

bool IsLastDayInMonth(stDate Date)
{
	return (Date.Day == NumberOfDaysInAMonth(Date.Month,
		Date.Year));
}
bool IsLastMonthInYear(short Month)
{
	return (Month == 12);
}

stDate IncreaseDateByOneDay(stDate Date)
{
	if (IsLastDayInMonth(Date))
	{
		if (IsLastMonthInYear(Date.Month))
		{
			Date.Month = 1;
			Date.Day = 1;
			Date.Year++;
		}
		else
		{
			Date.Day = 1;
			Date.Month++;
		}
	}
	else
	{
		Date.Day++;
	}
	return Date;
}
int GetDifferenceInDays(stDate Date1, stDate Date2, bool IncludeEndDay = false)
{
	int Days = 0;
	while (IsDate1BeforeDate2(Date1, Date2))
	{
		Days++;
		Date1 = IncreaseDateByOneDay(Date1);
	}
	return IncludeEndDay ? ++Days : Days;
}

// Get difference between two dates
int GetDifferenceInDays(stDate d1, stDate d2)
{
    int days1 = CalculateDaysInYear(d1);
    int days2 = CalculateDaysInYear(d2);

    return abs(days2 - days1);
}

stDate GetSystemDate()
{
	stDate Date;
	time_t t = time(0);
	tm* now = localtime(&t);
	Date.Year = now->tm_year + 1900;
	Date.Month = now->tm_mon + 1;
	Date.Day = now->tm_mday;
	return Date;
}

int main() {
	stDate Date1 = ReadFullDate();
	//here we enter the current date or read it from system
	stDate Date2 = GetSystemDate();
	cout << "Your age is in days is: " << GetDifferenceInDays(Date1, Date2, true);

	return 0;
}
