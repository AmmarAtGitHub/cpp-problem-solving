/*
===============================================================================
Problem: Check Period Overlap
===============================================================================

Goal
----
Create a program that determines whether two date periods overlap.
Two periods overlap if they share at least one common day.

Requirements
------------
- Read two periods (each with start and end dates)
- Compare dates accurately (year → month → day)
- Detect if periods overlap
- Provide both brute-force and optimized solutions
- Handle leap years correctly

Concepts Practiced
------------------
- Structs (custom data types)
- Divide and conquer (modular functions)
- Date comparison logic
- Nested loops (brute-force approach)
- Logical reasoning (optimized solution)
- Date increment handling

Real-World Applications
-----------------------
- Hotel booking systems:
  Prevent double-booking the same room for overlapping dates

- Car rental services:
  Ensure a car is not rented to two customers at the same time

- Meeting room scheduling:
  Detect conflicts between reservations

- Airline/train reservations:
  Manage seat availability across time periods

- Event planning systems:
  Avoid overlapping events in the same venue

Program Flow
------------
1. Read Period 1 (start and end dates).
2. Read Period 2 (start and end dates).
3. Check overlap using:
   - Brute-force (day-by-day comparison)
   - Optimized logic
4. Display results.

Example
-------
Input:
Period 1: 1/5/2025 → 10/5/2025
Period 2: 5/5/2025 → 15/5/2025

Output:
Yes (they overlap)


Notes
-----
The optimized solution is O(1) and is preferred in real systems,
while the brute-force approach is useful for learning and validation.

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

// Structure to hold a period
struct stPeriod {
    stDate StartDate;
    stDate EndDate;
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

// Read period
stPeriod ReadPeriod() {
    stPeriod Period;
    cout << "Enter start date:\n";
    Period.StartDate = ReadFullDate();

    cout << "\nEnter end date:\n";
    Period.EndDate = ReadFullDate();

    return Period;
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

// Compare dates
bool D1IsLessThanD2(stDate Date1, stDate Date2) {
    return (Date1.Year < Date2.Year) ||
           (Date1.Year == Date2.Year && Date1.Month < Date2.Month) ||
           (Date1.Year == Date2.Year && Date1.Month == Date2.Month && Date1.Day < Date2.Day);
}

// Check equality
bool D1IsEqualToD2(stDate Date1, stDate Date2) {
    return (Date1.Year == Date2.Year &&
            Date1.Month == Date2.Month &&
            Date1.Day == Date2.Day);
}

// Check if Date1 is after Date2
bool IsDate1AfterDate2(stDate Date1, stDate Date2) {
    return (!D1IsLessThanD2(Date1, Date2) && !D1IsEqualToD2(Date1, Date2));
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

// Difference in days
short GetDifferenceInDays(stDate Date1, stDate Date2, bool IncludeEndDay = false) {
    short Days = 0;
    while (D1IsLessThanD2(Date1, Date2)) {
        Days++;
        Date1 = IncreaseDateByOneDay(Date1);
    }
    return IncludeEndDay ? ++Days : Days;
}

// Brute-force overlap check
bool IsOverlapped(stPeriod Period1, stPeriod Period2) {
    stDate d1 = Period1.StartDate;

    while (!IsDate1AfterDate2(d1, Period1.EndDate)) {
        stDate d2 = Period2.StartDate;

        while (!IsDate1AfterDate2(d2, Period2.EndDate)) {
            if (D1IsEqualToD2(d1, d2))
                return true;

            d2 = IncreaseDateByOneDay(d2);
        }

        d1 = IncreaseDateByOneDay(d1);
    }

    return false;
}

// Optimized overlap check
bool IsOverlappedOptimized(stPeriod Period1, stPeriod Period2) {
    return !(IsDate1AfterDate2(Period1.StartDate, Period2.EndDate) ||
             IsDate1AfterDate2(Period2.StartDate, Period1.EndDate));
}

// Main
int main() {
    cout << "Enter period 1:\n";
    stPeriod Period1 = ReadPeriod();

    cout << "\nEnter period 2:\n";
    stPeriod Period2 = ReadPeriod();

    cout << "\nOverlap (Brute-force)? "
         << (IsOverlapped(Period1, Period2) ? "Yes" : "No") << endl;

    cout << "Overlap (Optimized)? "
         << (IsOverlappedOptimized(Period1, Period2) ? "Yes" : "No") << endl;

    return 0;
}