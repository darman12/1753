#include <iostream>
#include <iomanip>
using namespace std;

/******************************************
* This program displays a monthly calendar
* for a user-specified month and year
* DERP
* Created by Spencer Freebairn (darman12)
******************************************/

/**************************************
* Checks if given year is a leap year
**************************************/
bool isLeapYear(int year) {

	if (year % 4 != 0) {
        return false;
    }
    else if (year % 100 != 0) {
        return true;
    }
    else if (year % 400 != 0) {
        return false;
    }
    return true;
}

/**************************************
* Prompts user to input a month
**************************************/
int getMonth() {

	int num;
	do {	
		cout << "Enter a month number: ";
		cin >> num;
	}
	while (num < 1 || num > 12);
	return num;
}

/**************************************
* Prompts user to input a year
**************************************/
int getYear() {

	int num = 0;	
	
	do {	
		cout << "Enter a year: ";
		cin >> num;
	}
	while (num < 1753);
	return num;
}

/**************************************
* Returns the number of days in given 
* month of given year
**************************************/
int calcNumDays(int month, int year) {

	int daysByMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	
	if (isLeapYear(year) && month == 2) {
		return 29;
	}	
	return daysByMonth[month - 1];
}

/**************************************
* Counts num of days that have passed
* since Jan 1, 1753, returns remainder
* of days passed divided by 7
**************************************/
int computeOffset(int month, int year) {

	int daysSince1753 = 0;

	// adds days 366 days per leap year and 365 days per non-leap year
	// from 1753 (inclusively) to the year input by user (exclusively)
	for (int i = 1753; i < year; i++) {
		if (isLeapYear(i)) {
			daysSince1753 += 366;
		}
		else {
			daysSince1753 += 365;
		}
	}
	
	for (int i = 1; i < month; i++) {
		daysSince1753 += calcNumDays(i, year);
	}
	return daysSince1753 % 7;
}


/**************************************
* Displays the calendar
**************************************/
void displayCalendar(int month, int year, int offset, int numDays) {

	string monthNames[] = {
		"January", "February", "March", "April", "May", "June", "July",
		"August", "September", "October", "November", "December"};

	cout << "\n" << monthNames[month -1] << ", " << year << endl;
	cout << "  Su  Mo  Tu  We  Th  Fr  Sa" << endl;
	
	if (offset == 0) {
		cout << setw(7);
	}
	else if (offset == 6) {
		cout << setw(3);
	}
	else {
		cout << "  ";
		for (int i = 0; i <= offset; i++) {
			cout << "    ";
		}
	} 
	
	for (int i = 1; i <= numDays; i++) {
		if(offset == 6 && i == 1) {}
		else if ((i + offset) % 7 == 0) {
			cout << endl << "  ";	
		} 		

		if (i < 10) {
			cout << " " << i << "  ";  
		}
		else {
			cout << i << "  ";
		}	
	}
	cout << endl;
}

int main() {

	int month = getMonth();
	int year = getYear();
	int numDays = calcNumDays(month, year);	
	int offset = computeOffset(month, year);

	displayCalendar(month, year, offset, numDays);

    return 0;
}

