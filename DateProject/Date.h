#ifndef DATE_H 
#define DATE_H
#include <iostream>
#include <string>
using namespace std;

class Date;

// Function Prototypes for Overloaded Stream Operators 
ostream &operator << (ostream &, const Date &); 
istream &operator >> (istream &, Date &);

class Date{
private:
	int month;            // To hold a number of month
	string monthString;   // To hold a month of the year as a string
	int day;              // To hold a number of date
	int year;             // To hold a number of year
	
	void simplify();      // It nomalizes the date and is defined in Date.cpp

public:
	// Constructor
	Date();   
	Date(int month, int date, int year);
	
	// Destructor
	~Date(){};

	// Mutator
	void setMonth(int mm);  
	void setDay(int dd);
	void setYear(int yyyy);
	int getMonth() const { return month; }
	int getDay() const { return day; }
	int getYear() const { return year; }
	void monthOfYear();
	
	bool checkDate();     // It is true when the date is valid and is defined in Date.cpp
	bool isLeap();        // It is true when "year" is a leap year or the second month has 29 days and is defined in Date.cpp

	// Overloaded operator functions
	Date operator ++ (int);        // Postfix ++
	Date operator ++ ();           // Prefix ++
	Date operator -- (int);        // Postfix --
	Date operator -- ();           // Prefix --
	int operator - (const Date &); // Overloaded −
	bool operator>(const Date &);   // Overload >
	bool operator==(const Date &);  // Overload ==
	
	// Friends
	friend ostream &operator << (ostream &, const Date &);
    friend istream &operator >> (istream &, Date &);
};
#endif 
