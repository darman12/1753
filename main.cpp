/***************************************************************
* Project name: Calendar Project
* Author: Spencer Freebairn
*
* Description:
*   Displays the calendar of a month and year, later than
*   1753, specified by the user
*
* NOTES:
*   1/1/2017  - Functions are ordered alphabetically after main,
*               function prototypes are at the top
*             - Wrote stub stub functions for entire program, completed
*               following functions: getMonth(), getYear()
*             - Need to correct algorithm in computeOffset()
*   1/2/2017  - Created new function: checkIfLeapYear()
*             - Need to correct for loop in computeOffset()
*   1/8/2017  - Verified that algorithm in checkIfLeapYear() is correct
*   1/16/2017 - Working on algorithm in computeOffset()... it's a pain
*   1/19/2017 - computeOffset complete
*             - completed programming, needs to be tested for runtime
*               errors somehow
*
* Started: 1/1/2017 22:20
* Completed: 1/19/2017 21:44
***************************************************************/
#include <iostream>
#include <iomanip>
using namespace std;

int calcNumDays(int month, int year);
bool checkIfLeapYear(int yearCount);
int computeOffset(int month, int year);
void displayTable(int offset, int numDays);
int getMonth();
int getYear();
void printMonthYear(int month, int year);

int main()
{
    int month = getMonth();
    int year = getYear();

    int offset = computeOffset(month, year);
    printMonthYear(month, year);
    displayTable(offset, calcNumDays(month, year));

    return 0;
}

/****************************************
* Calculates the number of days in the
* the given month
****************************************/
int calcNumDays(int month, int year)
{
    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
    {
        return 31;
    }
    else if (month == 4 || month ==  6 || month == 9 || month == 11)
    {
        return 30;
    }
    else if (checkIfLeapYear(year) == true) // returns 29 days for Feb if it's leap year
    {
        return 29;
    }
    else                      // otherwise it returns 28 days for Feb
    {
        return 28;
    }
}

/*************************************
* Determines whether a given year is
* a leap year
*************************************/
bool checkIfLeapYear(int year)
{
    bool isLeapYear = false;

    if (year % 4 != 0)
    {
        isLeapYear = false;
    }
    else if (year % 100 != 0)
    {
        isLeapYear = true;
    }
    else if (year % 400 != 0)
    {
        isLeapYear = false;
    }
    else
    {
        isLeapYear = true;
    }
    return isLeapYear;
}

/*****************************************
* Calculates the offset for a given month
* and year
******************************************/
int computeOffset(int month, int year)
{
    int daysSince1753 = 0;

    // adds 365 days for each year from 1753 (inclusively) to
    //    the year specified (exclusively). Adds 366 days for
    //    leap years.
    for (int yearCount = 1753; yearCount < year; yearCount++)
    {
        bool isLeapYear = checkIfLeapYear(yearCount);
        if (isLeapYear == true)
        {
            daysSince1753 += 366;
        }
        else
        {
            daysSince1753 += 365;
        }
    }

    // adds number of days in each month of the year specified
    //    to total number of days passed since Jan 1, 1753
    //    until reaching month specified
    if (month == 1)
    {
        daysSince1753 += 0;
    }
    else if (month == 2)
    {
        daysSince1753 += 31;
    }
    else if (month == 3)
    {
        daysSince1753 += 59;
    }
    else if (month == 4)
    {
        daysSince1753 += 90;
    }
    else if (month == 5)
    {
        daysSince1753 += 120;
    }
    else if (month == 6)
    {
        daysSince1753 += 151;
    }
    else if (month == 7)
    {
        daysSince1753 += 181;
    }
    else if (month == 8)
    {
        daysSince1753 += 212;
    }
    else if (month == 9)
    {
        daysSince1753 += 243;
    }
    else if (month == 10)
    {
        daysSince1753 += 273;
    }
    else if (month == 11)
    {
        daysSince1753 += 304;
    }
    else if (month == 12)
    {
        daysSince1753 += 334;
    }

    // adds one more day if the month specified is past
    //    January and the year specified is a leap year
    //    to add extra day for Feb
    if (month >= 2 && checkIfLeapYear(year) == true)
    {
        daysSince1753 += 1;
    }

    return daysSince1753 % 7;
}

/****************************************
* Displays calendar table for the given
* month and year
****************************************/
void displayTable(int offset, int numDays)
{
    cout << "  Su  Mo  Tu  We  Th  Fr  Sa" << endl;

    int dayToPrint = 1;
    for (int count = offset + 1; count <= numDays + offset; count++)
    {
        if (dayToPrint == 1)
        {
            if (offset == 6)
            {
                cout << setw(4) << dayToPrint;
            }
            else
            {
                cout << setw(8 + (4 * offset)) << dayToPrint;
            }
        }
        else if (count % 7 != 0)
        {
            if (dayToPrint > 9)
            {
                cout << "  " << dayToPrint;
            }
            else
            {
                cout << "   " << dayToPrint;
            }
        }
        else
        {
            if (dayToPrint > 9)
            {
                cout << "\n  " << dayToPrint;
            }
            else
            {
                cout << "\n   " << dayToPrint;
            }

        }
        dayToPrint++;
    }
}

/******************************************
* Prompts the user to enter a month number,
* checks to make sure input is valid
******************************************/
int getMonth()
{
    int month;
    do
    {
        cout << "Enter a month number: ";
        cin >> month;
        if (month < 1 || month > 12)
        {
            cout << "Month must be between 1 and 12." << endl;
        }
    }
    while (month < 1 || month > 12);

    return month;
}

/******************************************
* Prompts the user to enter a year later
* than 1753
******************************************/
int getYear()
{
    int year;

    do
    {
        cout << "Enter year: ";
        cin >> year;
        if (year < 1753)
        {
            cout << "Year must be 1753 or later." << endl;
        }
    }
    while (year < 1753);

    return year;
}

/************************************
* Displays month in text then year in
* numbers before displayTable() displays
* the calendar
*********************************/
void printMonthYear(int month, int year)
{
    if (month == 1)
    {
        cout << "\nJanuary, " << year << endl;
    }
    else if (month == 2)
    {
        cout << "\nFebruary, " << year << endl;
    }
    else if (month == 3)
    {
       cout << "\nMarch, " << year << endl;
    }
    else if (month == 4)
    {
       cout << "\nApril, " << year << endl;
    }
    else if (month == 5)
    {
       cout << "\nMay, " << year << endl;
    }
    else if (month == 6)
    {
        cout << "\nJune, " << year << endl;
    }
    else if (month == 7)
    {
        cout << "\nJuly, " << year << endl;
    }
    else if (month == 8)
    {
        cout << "\nAugust, " << year << endl;
    }
    else if (month == 9)
    {
        cout << "\nSeptember, " << year << endl;
    }
    else if (month == 10)
    {
       cout << "\nOctober, " << year << endl;
    }
    else if (month == 11)
    {
       cout << "\nNovember, " << year << endl;
    }
    else if (month == 12)
    {
        cout << "\nDecember, " << year << endl;
    }
}
