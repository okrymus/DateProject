// It adds a day, substracts a day, writes it out in a different format and gives 
// the difference in days between two given days. 
// Author : Shradha Luintel, Panupong Leenawarat, Mohamed EL Hassnaoui

// Date: 03/26/2016 - started with setters and getters part (with validate input)
// Modified: 03/28/2016 - coded the functions
// Modified: 04/03/2016 - fixed bug that was coming up on the - operator (difference function)

#include <iostream>
#include "Date.h"

void test();

using namespace std;

int main() {
	cout << endl;
	cout << "  DATE OPERATOR " << endl << endl;
	test();

	system("pause");
	return 0;
}

void test() {
	Date date1, date2, dateBefore, dateAfter;

	do {
		cout << "\n  Enter a date" << endl;
		cin >> date1;

		if (date1.checkDate()) {
			cout << "\n  You entered: ";
			cout << date1;
			//testing leap year
			if (date1.isLeap()) {
				cout << "\n  " << date1.getYear() << " is a leap year";
			}
			else {
				cout << "\n  " << date1.getYear() << " is not a leap year";
			}
			cout << "\n  One day before this date :  ";

			//testing prefix -- overloading
			dateBefore = --date1;

			//reset the date1's value
			date1++;

			cout << dateBefore << endl;

			cout << "  One day after this date: ";

			//testing postfix ++ overloading
			dateAfter = date1++;
			dateAfter++;

			//reset date1
			date1--;

			cout << dateAfter << endl;

			do {
				cout << "\n  Enter another date: " << endl;
				cin >> date2;
			} while (!date2.checkDate());

			//testing date difference
			cout << "\n  Difference between given dates :  " << date2 - date1;
			cout << endl << endl;
		}
	} while (!date1.checkDate());
}
