#ifndef LIBRARY_H_
#define LIBRARY_H_

#include "book.h"
#include "person.h"
#include <fstream>

#define bookNum 46

class Library {
private:
	string name;
	Book books[bookNum];
	Person owner;
public:
	Library();
	// setters
	void setName(string n) { name = n; }
	void setOwner(Person p) { owner = p;}
	int setBooks(string, int);
	// getters
	string getName() { return name; }
	Person getOwner() { return owner; }

	void print(ostream &);
};
#endif