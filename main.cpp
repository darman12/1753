#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

int calcNumDays(int month, int year);
bool checkFile();
bool checkIfLeapYear(int yearCount);
int computeOffset(int month, int year);
void displayTable(int offset, int numDays);
int getMonth();
int getYear();
void printMonthYear(int month, int year);

char fileName[256];

int main()
{
    cout << "What is the name of the file you wish to have the calendar"
         << " saved in? ";
    cin >> fileName;
    while (checkFile() == false) {
        cout << "Cannot write to that file, please select another: " << endl;
        cin >> fileName;
    }
    cout << "Your calendar will be saved in \"" << fileName << "\"." << endl;
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
    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 ||
        month == 10 || month == 12)
    {
        return 31;
    }
    else if (month == 4 || month ==  6 || month == 9 || month == 11)
    {
        return 30;
    }
    else if (checkIfLeapYear(year) == true) // returns 29 days for Feb if it's
    {                                       //    leap year
        return 29;
    }
    else                      // otherwise it returns 28 days for Feb
    {
        return 28;
    }
}

/******************************************
* Checks to see if the specified file can
* be writeen to
******************************************/
bool checkFile()
{
    ofstream fout(fileName, ios::app);
    if (fout.fail()) {
        return false;
    }

    fout.close();
    return true;
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
    for (int i = 1; i < month; i++)
    {
        daysSince1753 += calcNumDays(i, year);
    }

    return daysSince1753 % 7;
}

/****************************************
* Displays calendar table for the given
* month and year
****************************************/
void displayTable(int offset, int numDays)
{
    ofstream fout(fileName, ios::app);

    fout << "  Su  Mo  Tu  We  Th  Fr  Sa" << endl;

    int dayToPrint = 1;
    for (int count = offset + 1; count <= numDays + offset; count++)
    {
        if (dayToPrint == 1)
        {
            if (offset == 6)
            {
                fout << setw(4) << dayToPrint;
            }
            else
            {
                fout << setw(8 + (4 * offset)) << dayToPrint;
            }
        }
        else if (count % 7 != 0)
        {
            if (dayToPrint > 9)
            {
                fout << "  " << dayToPrint;
            }
            else
            {
                fout << "   " << dayToPrint;
            }
        }
        else
        {
            if (dayToPrint > 9)
            {
                fout << "\n  " << dayToPrint;
            }
            else
            {
                fout << "\n   " << dayToPrint;
            }

        }
        dayToPrint++;
    }
    fout << "\n\n";
    fout.close();
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
    ofstream fout(fileName, ios::app);

    if (month == 1)
    {
        fout << "January, " << year << endl;
    }
    else if (month == 2)
    {
        fout << "February, " << year << endl;
    }
    else if (month == 3)
    {
       fout << "March, " << year << endl;
    }
    else if (month == 4)
    {
       fout << "April, " << year << endl;
    }
    else if (month == 5)
    {
       fout << "May, " << year << endl;
    }
    else if (month == 6)
    {
        fout << "June, " << year << endl;
    }
    else if (month == 7)
    {
        fout << "July, " << year << endl;
    }
    else if (month == 8)
    {
        fout << "August, " << year << endl;
    }
    else if (month == 9)
    {
        fout << "September, " << year << endl;
    }
    else if (month == 10)
    {
       fout << "October, " << year << endl;
    }
    else if (month == 11)
    {
       fout << "November, " << year << endl;
    }
    else if (month == 12)
    {
        fout << "December, " << year << endl;
    }
    fout.close();
}
