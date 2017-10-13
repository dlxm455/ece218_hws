#ifndef DATE_H_
#define DATE_H_

#include <iostream>

using namespace std;

class Date {
private:
	int year;
	int month;
	int day;

public:
	void init(int); // a setter with an int parameter formatted as YYYYMMDD
	string getFormattedString(); // a getter returning YYYYMMDD string 
	void print(ostream &); // print the date as YYYYMMDD 
};

#endif

