#ifndef VALIDATEINPUT_H
#define VALIDATEINPUT_H
#include <iostream>
using namespace std;

class ValidateInput{
private:
public:
	int getIntInRange(double startPoint, double endPoint, istream &os = cin);
	int getInteger(istream &os = cin);
	double getNum(istream &os = cin);
	int getIntPosNum(istream &os = cin);
	double getPosNum(istream &os = cin);
};
#endif // !VALIDATEINPUT_H
