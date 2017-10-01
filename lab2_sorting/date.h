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
	void init(int);
	string getFormattedString(); 
	void print(ostream &); 
};

#endif

