/*
===============================================================================
Problem: Vacation Return Date (Business Days Only)
===============================================================================

Goal
----
Create a program that calculates the return date after a vacation,
considering only business days (excluding weekends).

Requirements
------------
- Read vacation start date
- Read vacation duration (in days)
- Count only business days (Mon–Fri)
- Skip weekends automatically
- Adjust return date if it lands on weekend
- Handle leap years correctly

Concepts Practiced
------------------
- Structs (custom data types)
- Divide and conquer (modular design)
- Date increment logic
- Business day filtering
- Gregorian calendar calculations
- Looping and conditionals

Program Flow
------------
1. Read vacation start date.
2. Read vacation duration.
3. Increment date day by day:
   - Count only business days
   - Skip weekends
4. If return date falls on weekend:
   - Move to next Monday
5. Display final return date.

Functions
---------
ReadFullDate()                 -> Reads full date from user
isLeapYear()                   -> Checks leap year
NumberOfDaysInAMonth()         -> Days in a month
IncreaseDateByOneDay()         -> Moves date forward
DayOfWeekOrder()               -> Calculates weekday index
DayName()                      -> Converts index to name
IsBusinessDay()                -> Checks business day
CalculateVacationReturnDate()  -> Computes return date

Example
-------
Input:
Start Date: 1/5/2025
Duration: 5 days

Output:
Vacation starts: Thu, 1/5/2025
Return date: Thu, 8/5/2025

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

// Check business day
bool IsBusinessDay(stDate Date) {
    short d = DayOfWeekOrder(Date);
    return (d != 0 && d != 6);
}

// Calculate return date based on business days
stDate CalculateVacationReturnDate(stDate DateFrom, short Duration) {
    stDate ReturnDate = DateFrom;

    while (Duration > 0) {
        if (IsBusinessDay(ReturnDate)) {
            Duration--;
        }
        ReturnDate = IncreaseDateByOneDay(ReturnDate);
    }

    // Adjust if weekend
    short d = DayOfWeekOrder(ReturnDate);

    if (d == 0) { // Sunday → Monday
        ReturnDate = IncreaseDateByOneDay(ReturnDate);
    } else if (d == 6) { // Saturday → Monday
        ReturnDate = IncreaseDateByOneDay(ReturnDate);
        ReturnDate = IncreaseDateByOneDay(ReturnDate);
    }

    return ReturnDate;
}

// Main
int main() {
    cout << "Vacation start:\n";
    stDate Date1 = ReadFullDate();

    short Duration;
    cout << "\nPlease enter vacation duration (in days): ";
    cin >> Duration;

    stDate ReturnDate = CalculateVacationReturnDate(Date1, Duration);

    cout << "\nVacation starts: "
         << DayName(DayOfWeekOrder(Date1)) << ", "
         << Date1.Day << "/" << Date1.Month << "/" << Date1.Year << endl;

    cout << "Return date: "
         << DayName(DayOfWeekOrder(ReturnDate)) << ", "
         << ReturnDate.Day << "/" << ReturnDate.Month << "/" << ReturnDate.Year << endl;

    return 0;
}