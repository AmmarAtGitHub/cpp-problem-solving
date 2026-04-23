/*
===============================================================================
Problem: Date Insights (Week, Month, Year Calculations)
===============================================================================

Goal
----
Create a program that takes a specific date and provides useful insights such as:
- Day of the week
- Whether it is a weekend or business day
- Days remaining until the end of the week, month, and year

Requirements
------------
- Read a full date (day, month, year) from the user
- Determine the correct day of the week using the Gregorian calendar
- Identify weekend and business days
- Handle leap years correctly
- Calculate remaining days in week, month, and year

Concepts Practiced
------------------
- Structs (custom data types)
- Divide and conquer (modular functions)
- Gregorian calendar calculations
- Leap year logic
- Conditional logic
- Arrays and indexing

Program Flow
------------
1. Read the full date from the user.
2. Calculate the day of the week.
3. Check if it's weekend or business day.
4. Calculate remaining days:
   - Until end of week
   - Until end of month
   - Until end of year
5. Display all results.

Functions
---------
ReadFullDate()           -> Reads full date from user
DayOfWeekOrder()         -> Calculates day index using Gregorian formula
DayName()                -> Converts index to day name
IsWeekEnd()              -> Checks if date is weekend
IsBusinessDay()          -> Checks if date is business day
DaysUntilEndOfWeek()     -> Remaining days in week
isLeapYear()             -> Checks leap year
NumberOfDaysInAMonth()   -> Returns days in a month
DaysTillEndOfMonth()     -> Remaining days in month
DaysTillEndOfYear()      -> Remaining days in year

Example
-------
Input:
Day: 10
Month: 4
Year: 2025

Output:
Today is Thu, 10/4/2025
Is it weekend? No
Days until end of week: 3
Days until end of month: 20
Days until end of year: 265

===============================================================================
*/

#include <iostream>
using namespace std;

// Structure to hold date
struct stDate {
    short Year;
    short Month;
    short Day;
};

// Function to read day
short ReadDay() {
    short Day;
    cout << "\nPlease enter a Day? ";
    cin >> Day;
    return Day;
}

// Function to read month
short ReadMonth() {
    short Month;
    cout << "\nPlease enter a Month? ";
    cin >> Month;
    return Month;
}

// Function to read year
short ReadYear() {
    short Year;
    cout << "\nPlease enter a Year? ";
    cin >> Year;
    return Year;
}

// Function to read full date
stDate ReadFullDate() {
    stDate Date;
    Date.Day = ReadDay();
    Date.Month = ReadMonth();
    Date.Year = ReadYear();
    return Date;
}

// Gregorian calendar formula to get day of week
short DayOfWeekOrder(short year, short month, short day) {
    short a = (14 - month) / 12;
    short y = year - a;
    short m = month + (12 * a - 2);

    // Returns value from 0 (Sunday) to 6 (Saturday)
    short d = (day + y + y / 4 - y / 100 + y / 400 + (31 * m / 12)) % 7;
    return d;
}

// Overloaded version using struct
short DayOfWeekOrder(stDate Date) {
    return DayOfWeekOrder(Date.Year, Date.Month, Date.Day);
}

// Convert day index to name
string DayName(short dayOfWeekOrder) {
    string dayNames[7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
    return dayNames[dayOfWeekOrder];
}

// Check if weekend (Saturday or Sunday)
bool IsWeekEnd(stDate Date) {
    short d = DayOfWeekOrder(Date);
    return (d == 0 || d == 6);
}

// Check if business day
bool IsBusinessDay(stDate Date) {
    return !IsWeekEnd(Date);
}

// Days remaining until end of week
short DaysUntilEndOfWeek(stDate Date) {
    short d = DayOfWeekOrder(Date);
    return (d == 0) ? 0 : 7 - d;
}

// Check leap year
bool isLeapYear(short Year) {
    return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
}

// Days in a month
short NumberOfDaysInAMonth(short Month, short Year) {
    if (Month < 1 || Month > 12)
        return 0;

    int days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

    return (Month == 2) ? (isLeapYear(Year) ? 29 : 28)
                        : days[Month - 1];
}

// Days remaining in month
short DaysTillEndOfMonth(stDate Date) {
    return NumberOfDaysInAMonth(Date.Month, Date.Year) - Date.Day;
}

// Days remaining in year
short DaysTillEndOfYear(stDate Date) {
    short total = DaysTillEndOfMonth(Date);

    // Add remaining months
    for (short i = Date.Month + 1; i <= 12; i++) {
        total += NumberOfDaysInAMonth(i, Date.Year); // FIXED BUG
    }

    return total;
}

// Main program
int main() {
    stDate Date = ReadFullDate();

    cout << "\nToday is "
         << DayName(DayOfWeekOrder(Date)) << ", "
         << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;

    cout << "Is it weekend? "
         << (IsWeekEnd(Date) ? "Yes" : "No") << endl;

    cout << "Is it a business day? "
         << (IsBusinessDay(Date) ? "Yes" : "No") << endl;

    cout << "Days until end of week: "
         << DaysUntilEndOfWeek(Date) << " Day(s)." << endl;

    cout << "Days until end of month: "
         << DaysTillEndOfMonth(Date) << " Day(s)." << endl;

    cout << "Days until end of year: "
         << DaysTillEndOfYear(Date) << " Day(s)." << endl;

    return 0;
}
