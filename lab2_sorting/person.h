#ifndef PERSON_H_
#define PERSON_H_

#include "date.h"
#include <iostream>
#include <string>

using namespace std;

class Person {
private:
	int ssn;
	string firstName, lastName;
	Date birthday;
public:
	Person(); // default constructor
	Person(string, string, string, string); // alternative constructor
	void print(ostream &);
	int compare(Person &); // compare by last name
	
	/*
	void setSSN(int s) { ssn = s; }
	void setFirstName(string fN) { firstName = fN; }
	void setLastName(string lN) { lastName = lN; }
	void setBirthday(Date b) { birthday = b; }
	*/

	// a 'combined' setter	
	void init(int s, string fN, string lN, Date b) { 
		ssn = s;
		firstName = fN;
		lastName = lN;
		birthday = b;
	}
	
	// getters
	int getSSN() { return ssn; }
	string getFirstName() { return firstName; }
	string getLastName() { return lastName; }
	Date getBirthday() { return birthday; }
	
};

#endif

