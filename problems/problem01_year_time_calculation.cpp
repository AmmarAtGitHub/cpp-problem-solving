/*
Problem Goal:
-------------
Create a program that calculates the total number of days, hours, minutes,
and seconds in a given year.

The program must correctly handle both:
- Regular years (365 days)
- Leap years (366 days)

Concepts Practiced:
-------------------
- Divide and conquer approach (breaking the problem into smaller functions)
- Function design and reuse
- Leap year calculation logic
- Basic input/output in C++
- Simple arithmetic operations

Program Flow:
-------------
1. Read a year from the user.
2. Determine if the year is a leap year.
3. Calculate:
   - Number of days in the year
   - Number of hours in the year
   - Number of minutes in the year
   - Number of seconds in the year
4. Display the results to the user.
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;


// Divide and Conquer Approach:
// The problem is broken down into smaller, independent functions.
// Each function is responsible for a single task, making the code
// easier to understand, test, and maintain.
//
// Requirements:
// - Function to check if a year is a leap year
// - Function to calculate the number of days in a year
// - Function to calculate the number of hours in a year
// - Function to calculate the number of minutes in a year
// - Function to calculate the number of seconds in a year




bool IsLeapYear(short year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

//function to calculate the days in year
short CalculateDays(short year) {
    short days = IsLeapYear(year) ? 366 : 365;
    return days;
}

//function to calculate the hours in year
short CalculateHours(short year) {
    short hours = IsLeapYear(year) ? 366 * 24 :  365 * 24;
    return hours;
}

//function to calculate the minutes in year
int CalculateMinutes(short year) {
    int minutes = IsLeapYear(year) ? 366 * 24 * 60 : 365 * 24 * 60;
    return minutes;
}

//function to calculate the seconds in year
int CalculateSeconds(short year) {
    int seconds = IsLeapYear(year) ? 366 * 24 * 60 * 60 : 365 * 24 * 60 * 60;
    return seconds;
}

short ReadYear() {
    short year = 0;
    cout << "Please enter a year: " << endl;
    cin >> year;
    return year;
}

void CalculateTimeInYear(short year) {
    cout << "Number of days in year " + to_string(year) + " is " + to_string(CalculateDays(year)) << endl;
    cout << "Number of hours in year " + to_string(year) + " is " + to_string(CalculateHours(year)) << endl;
    cout << "Number of minutes in year " + to_string(year) + " is " + to_string(CalculateMinutes(year)) << endl;
    cout << "Number of seconds in year " + to_string(year) + " is " + to_string(CalculateSeconds(year)) << endl;
}


// Entry point of program
int main()
{
    CalculateTimeInYear(ReadYear());
    return 0;
}