#ifndef DATE_H_
#define DATE_H_

#include <iostream>

using namespace std;

class Data {
private:
	int year;
	int month;
	int day;

public:
	void setProperties(int);
	void print(ostream &); 
};

#endif

