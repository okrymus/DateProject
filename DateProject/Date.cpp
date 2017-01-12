#include "Date.h"
#include "ValidateInput.h"

Date::Date(int mm, int dd, int yyyy)
{
	setMonth(mm);
	setDay(dd);
	setYear(yyyy);

}

Date::Date(){
	setMonth(01);
	setDay(01);
	setYear(1900);
}

//***************************************************************************
// Definition of member function simplify. This function checks for values  *
// in the day member greater than the number of days in the month member.   *
// If such a value is found, the numbers numbers in month,day and year are  *
// adjusted to conform to a valid date expression.                          *
//***************************************************************************

void Date::simplify(){
	int daysInMonths[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (isLeap())
		daysInMonths[1] = 29;

	// Normalize the date 
	// If "day" is greater than the number of day in the month
	if (!checkDate() && day > daysInMonths[month - 1])
	{
		if (day % daysInMonths[month - 1] == 1 && month != 12)
		{
			month += 1;
			day = 1;
		}
		else if (day % daysInMonths[month - 1] == 1 && month == 12)
		{
			month = 1;
			day = 1;
		}
	}
	else if (!checkDate() && day <= 0)
	{
		if (month != 1)
		{
			month -= 1;
			day = daysInMonths[month - 1];
		}
		else
		{
			month = 12;
			day = daysInMonths[month - 1];
			year -= 1;
		}
	}
	monthOfYear();
}

//**************************************************************************************
// Definition of member function checkDate. It checks the day, month and year member   *
// in date class is legal date or not.                                                 *
// It returns true when the input date is legal date returns false when the            *
// input date is not legal date.                                                       *             
//**************************************************************************************

bool Date::checkDate()
{
	bool result = true;
	int daysInMonths[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	if (year < 1900 || year>2100)
		result = false;
	if (isLeap())
		daysInMonths[1] = 29;
	if (day < 1 || day > daysInMonths[month - 1])
		result = false;
	return result;
}

//*************************************************************************
// Definition of member function isLeap. It returns true when the year    *
// member in the class has 29 days in February or returns false when the  *
// year has 28 days in February                                           *
//*************************************************************************

bool Date::isLeap()
{
	if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
		return true;
	else
		return false;
}

void Date::setMonth(int mm)
{
	ValidateInput validInput;                           // Create ValidateInput's object which accepts only valid input

	if (mm > 12 || mm < 1)
	{
		cout << "\t!!Invalid month, try again :";
		mm = validInput.getIntInRange(1, 12);
	}
	this->month = mm;
	monthOfYear();
}

void Date::setDay(int dd)
{
	ValidateInput validInput;                            // Create ValidateInput's object which accepts only valid input
	int daysInMonths[] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int numOfDay = daysInMonths[month - 1];

	if (dd > numOfDay || dd < 1)
	{
		cout << "\t !!Invalid date, try again: ";
		dd = validInput.getIntInRange(1, numOfDay);
	}
	this->day = dd;
}

//****************************************************************************************
// Definition of member function monthOfYear.  A number of month "month" member in the   *
// date class must be in range between 1 and 12                                          *
//  It sets monthString is a month of year                                               *
//****************************************************************************************

void Date::monthOfYear()
{
	switch (month)
	{
	case 1: monthString = "January";  break;
	case 2: monthString = "February"; break;
	case 3: monthString = "March";  break;
	case 4: monthString = "April";  break;
	case 5: monthString = "May";  break;
	case 6: monthString = "June";  break;
	case 7: monthString = "July";  break;
	case 8: monthString = "August";  break;
	case 9: monthString = "September";  break;
	case 10: monthString = "October";  break;
	case 11: monthString = "November";  break;
	case 12: monthString = "December";  break;
	default:  monthString = "Undefine month";
	}
}

//*************************************************************************************
// Overloading the prefix ++ operator. It increment the object's day member           *
// When a date is set to the last day of the month and incremented, it should become  *
// the first day of the following month                                               *
// When a date is set to December 31 and incremented, it should become                *
// January 1 of the following year.                                                   *
//*************************************************************************************

Date Date::operator++(){
	++day;
	// Normalize the date 
	simplify();

	return *this;
}

//*************************************************************************************
// Overloading the postfix ++ operator. It increment the object's day member          *
// When a date is set to the last day of the month and incremented, it should become  *
// the first day of the following month                                               *
// When a date is set to December 31 and incremented, it should become                *
// January 1 of the following year.                                                   *
//*************************************************************************************

Date Date::operator++(int){
	Date temp(month, day, year);
	day++;
	// Normalize the date 
	simplify();

	return temp;
}

//************************************************************************************
// Overloading the prefix -- operator.  It decrement the object's day member         *
// When a day is set to the first day of the month and decremented, it should become *
// the last day of the previous month.                                               *
// When a date is set to January 1 and decremented, it should become December        *
// 31 of the previous year.                                                          *
//************************************************************************************

Date Date::operator--(){
	--day;
	// Normalize the date 
	simplify();

	return *this;
}

//************************************************************************************
// Overloading the postfix -- operator.  It decrement the object's day member        *
// When a day is set to the first day of the month and decremented, it should become *
// the last day of the previous month.                                               *
// When a date is set to January 1 and decremented, it should become December        *
// 31 of the previous year.                                                          *
//************************************************************************************

Date Date::operator--(int){
	Date temp(month, day, year);
	day--;
	// Normalize the date 
	simplify();

	return temp;
}

//****************************************************************************************
// Overloading the Subtraction operator. If one Date object is subtracted from another,  *
// the operator should give the number of days between the two dates. For example,       *
// if April 10, 2014 is subtracted from April 18, 2014, the result will be 8.            *
// It return the number days between the two dates as an integer                         *
//****************************************************************************************

int Date::operator - (const Date &right)
{
	int daysInMonths[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int reg_year = 365;
	int years_difference, months_total, days_difference;;


	// Process to get the years difference
	if (year == right.year)
		years_difference = 0;
	else
	{
		// The year must not be the leap year
		if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
		{
			if (right.year % 4 == 0 && right.year % 100 != 0 || right.year % 400 == 0)
			{
				if (year > right.year)
					years_difference = (year - right.year) * (reg_year)+2;
				else
					years_difference = (right.year - year) * (reg_year)+2;

				if (right.month > month)
					if (daysInMonths[month - 1] > daysInMonths[1])
						--years_difference;
			}
			else
			{
				if (year > right.year)
					years_difference = (year - right.year) * (reg_year)+1;
				else
					years_difference = (right.year - year) * (reg_year)+1;

				if (month > right.month)
					if (daysInMonths[right.month - 1] > daysInMonths[1])
						--years_difference;
			}
		}
		else
		{
			if (year > right.year)
				years_difference = (year - right.year) * (reg_year);
			else
				years_difference = (right.year - year) * (reg_year);
		}
	}

	// Process it to get the month total between two dates
	if (month == right.month)
		months_total = 0;
	else
	{
		if (month > right.month)
			for (int i = (month - 1); i > (right.month - 1); i--)
			{
				static int months_total_temp = 0;
				months_total_temp += daysInMonths[i];
				months_total = months_total_temp;
			}
		else
			for (int i = (month - 1); i < (right.month - 1); i++)
			{
				static int months_total_temp = 0;
				months_total_temp += daysInMonths[i];
				months_total = months_total_temp;
			}
	}

	int days_total;

	// Process to get the total of days between two dates
	if (day == right.day)
	{
		days_difference = 0;
		days_total = (years_difference + months_total) - days_difference;
	}
	else
	{
		if (day > right.day)
		{
			days_difference = day - right.day;

			days_total = (years_difference + months_total) - days_difference;
		}
		else
		{
			days_difference = right.day - day;

			days_total = (years_difference + months_total) + days_difference;
		}
	}

	// In Between Leap Years
	if (year != right.year)
	{
		if (year > right.year)
			for (int i = (right.year + 1); i < year; i++)
				if (i % 4 == 0 && i % 100 != 0 || i % 400 == 0)
					++days_total;
				else
					for (int i = (year + 1); i < right.year; i++)
						if (i % 4 == 0 && i % 100 != 0 || i % 400 == 0)
							++days_total;
	}

	// If days_total is a negative number, process it
	if (days_total < 0)
		days_total *= -1;

	// Return to days total between two dates
	return days_total;
}

void Date::setYear(int yyyy)
{
	ValidateInput validInput;                           // Create ValidateInput's object which accepts only valid input
	this->year = yyyy;

	// While the year is not valid, process it
	while (!checkDate())
	{
		cout << "\t!! Invalid year, try again: ";        // Display massage
		year = validInput.getIntInRange(1900, 2100);     // Calling the getIntInRange from ValidateInput class to get only valid year
	}
}

//***************************************************************************************************
// Overloading the stream insertion operator (<<).                                                  *
// The function has two parameters: an ostream reference object and a const Date reference object.  *
// It returns a reference to an ostream object.                                                     *
//***************************************************************************************************

ostream &operator << (ostream &strm, const Date &obj) {
	strm << obj.monthString << " " << obj.day << " , " << obj.year;
	return strm;
}

//***************************************************************************************************
// Overloading the stream extraction operator (>>).                                                 *
// The function has two parameters: an istream reference object and a const Date reference object.  *
// It returns a reference to an istream object.                                                     *
//***************************************************************************************************

istream &operator >> (istream &strm, Date &obj) {
	ValidateInput validInput;

	// Prompt the user for the month. 
	cout << "   Month: ";
	obj.month = validInput.getIntInRange(1, 12, strm);
	// Prompt the user for the day. 
	cout << "   Date: ";
	obj.day = validInput.getIntInRange(1, 31, strm);
	// Prompt the user for the year. 
	cout << "   Year: ";
	obj.year = validInput.getIntInRange(1900, 2100, strm);;

	if (!obj.checkDate())
		cout << "\t!!Invalid Date\n";

	// Normalize the date
	obj.simplify();

	return strm;
}

//***************************************************************************************************
// Overloading the greater operator (>).                                                            *
// The function has one parameters: a const Date reference object.                                  *
// It return true when the const Date reference object is the date before                           *
//***************************************************************************************************

bool Date::operator>(const Date &obj) {
	if (year > obj.getYear()) {
		return true;
	}
	else if (year == obj.getYear()) {
		if (month > obj.getMonth()) {
			return true;
		}
		else if (month == obj.getMonth()) {
			return day > obj.getDay();
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}

}

//***************************************************************************************************
// Overloading the equal operator (==).                                                             *
// The function has one parameters: a const Date reference object.                                  *
// It return true when the const Date reference object is same the dates                            *
//***************************************************************************************************

bool Date::operator==(const Date &obj) {
	if (year == obj.getYear() && month == obj.getMonth() && day == obj.getDay())
		return true;
	else
		return false;
}
