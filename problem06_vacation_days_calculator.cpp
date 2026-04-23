/*
===============================================================================
Problem: Calculate Actual Vacation Days (Exclude Weekends)
===============================================================================

Goal
----
Create a program that calculates the number of actual vacation days
between two dates, excluding weekends (Saturday and Sunday).

Requirements
------------
- Read start and end dates from the user
- Correctly calculate total days between two dates
- Exclude weekends from the count
- Handle leap years properly
- Use Gregorian calendar for day calculations

Concepts Practiced
------------------
- Structs (custom data types)
- Divide and conquer (modular design)
- Date comparison logic
- Date increment (day-by-day)
- Leap year handling
- Looping and conditionals

Program Flow
------------
1. Read vacation start date.
2. Read vacation end date.
3. Calculate total days between the two dates.
4. Loop through each day:
   - Skip weekends (Saturday & Sunday)
   - Count only business days
5. Display actual vacation days.

Functions
---------
ReadFullDate()               -> Reads full date from user
isLeapYear()                 -> Checks if year is leap
NumberOfDaysInAMonth()       -> Returns days in a month
IsDate1BeforeDate2()         -> Compares two dates
IncreaseDateByOneDay()       -> Moves date forward
GetDifferenceInDays()        -> Total days between dates
DayOfWeekOrder()             -> Calculates day index
DayName()                    -> Converts index to name
CalculateActualVacationDays()-> Counts days excluding weekends

Example
-------
Input:
Start Date: 1/5/2025
End Date:   10/5/2025

Output:
Actual vacation days: 6

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

// Read day
short ReadDay() {
    short Day;
    cout << "\nPlease enter a Day? ";
    cin >> Day;
    return Day;
}

// Read month
short ReadMonth() {
    short Month;
    cout << "\nPlease enter a Month? ";
    cin >> Month;
    return Month;
}

// Read year
short ReadYear() {
    short Year;
    cout << "\nPlease enter a Year? ";
    cin >> Year;
    return Year;
}

// Read full date
stDate ReadFullDate() {
    stDate Date;
    Date.Day = ReadDay();
    Date.Month = ReadMonth();
    Date.Year = ReadYear();
    return Date;
}

// Check leap year
bool isLeapYear(short Year) {
    return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
}

// Days in month
short NumberOfDaysInAMonth(short Month, short Year) {
    if (Month < 1 || Month > 12)
        return 0;

    int days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

    return (Month == 2) ? (isLeapYear(Year) ? 29 : 28)
                        : days[Month - 1];
}

// Compare two dates
bool IsDate1BeforeDate2(stDate Date1, stDate Date2) {
    return (Date1.Year < Date2.Year) ||
           (Date1.Year == Date2.Year && Date1.Month < Date2.Month) ||
           (Date1.Year == Date2.Year && Date1.Month == Date2.Month && Date1.Day < Date2.Day);
}

// Check last day in month
bool IsLastDayInMonth(stDate Date) {
    return (Date.Day == NumberOfDaysInAMonth(Date.Month, Date.Year));
}

// Check last month in year
bool IsLastMonthInYear(short Month) {
    return (Month == 12);
}

// Increase date by one day
stDate IncreaseDateByOneDay(stDate Date) {
    if (IsLastDayInMonth(Date)) {
        if (IsLastMonthInYear(Date.Month)) {
            Date.Day = 1;
            Date.Month = 1;
            Date.Year++;
        } else {
            Date.Day = 1;
            Date.Month++;
        }
    } else {
        Date.Day++;
    }
    return Date;
}

// Get difference in days
int GetDifferenceInDays(stDate Date1, stDate Date2, bool IncludeEndDay = false) {
    int Days = 0;
    while (IsDate1BeforeDate2(Date1, Date2)) {
        Days++;
        Date1 = IncreaseDateByOneDay(Date1);
    }
    return IncludeEndDay ? ++Days : Days;
}

// Gregorian formula
short DayOfWeekOrder(short year, short month, short day) {
    short a = (14 - month) / 12;
    short y = year - a;
    short m = month + (12 * a - 2);

    return (day + y + y / 4 - y / 100 + y / 400 + (31 * m / 12)) % 7;
}

// Overload
short DayOfWeekOrder(stDate Date) {
    return DayOfWeekOrder(Date.Year, Date.Month, Date.Day);
}

// Day name
string DayName(short d) {
    string names[7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
    return names[d];
}

// Calculate actual vacation days (excluding weekends)
int CalculateActualVacationDays(stDate DateFrom, stDate DateTo) {
    int count = 0;
    int totalDays = GetDifferenceInDays(DateFrom, DateTo, true);

    for (int i = 0; i < totalDays; i++) {
        DateFrom = IncreaseDateByOneDay(DateFrom);

        short d = DayOfWeekOrder(DateFrom);

        // Count only business days
        if (d != 0 && d != 6) {
            count++;
        }
    }

    return count;
}

// Main
int main() {
    cout << "Vacation start:\n";
    stDate Date1 = ReadFullDate();

    cout << "\nVacation end:\n";
    stDate Date2 = ReadFullDate();

    cout << "\nVacation from: "
         << DayName(DayOfWeekOrder(Date1)) << ", "
         << Date1.Day << "/" << Date1.Month << "/" << Date1.Year << endl;

    cout << "Vacation to: "
         << DayName(DayOfWeekOrder(Date2)) << ", "
         << Date2.Day << "/" << Date2.Month << "/" << Date2.Year << endl;

    cout << "\nActual vacation days (excluding weekends): "
         << CalculateActualVacationDays(Date1, Date2) << endl;

    return 0;
}