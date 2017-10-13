#include "date.h"
#include <iomanip>



// a setter to set year, month, day with an int parameter formatted as YYYYMMDD

void Date::init(int fD) {
	// parse integer with format YYYYMMDD
	int dd = fD % 100;
	fD /= 100;
	int mm = fD % 100;
	int yy = fD / 100;

	year = yy;
	month = mm;
	day = dd;
}




// convert int to string given number of digits (padding zero in front)
// ex. (numDigit = 2, data = 4) => '04' 

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



// a getter to get a string with YYYYMMDD format from the date struct
	
string Date::getFormattedString() {
	string s = itoFormattedString(4, year); 
	s += itoFormattedString(2, month);
	s += itoFormattedString(2, day);
	return s;
}




// print out YYYYMMDD
	
void Date::print(ostream & out) {
	out << getFormattedString() << endl;
}

