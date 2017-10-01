#include "date.h"
#include <iomanip>

void Date::init(int fD) {
	int dd = fD % 100;
	int mm = fD % 10000 / 100;
	int yy = fD / 10000;

	year = yy;
	month = mm;
	day = dd;
}

string itoFormattedString(int numDigit, int data) {
	string s = "";
	for (int i = 0; i < numDigit; i++) {
		s += "0";
	}
	int count = 0;
	while (data > 0 && count < numDigit) {
		s[numDigit - 1 - count] = (data % 10) + '0';
		data /= 10;
		count ++;
	}
	return s;
}
		
string Date::getFormattedString() {
	string s = itoFormattedString(4, year); 
	s += itoFormattedString(2, month);
	s += itoFormattedString(2, day);
	return s;
}
	
void Date::print(ostream & out) {
	out << getFormattedString() << endl;
}

