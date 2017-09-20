#ifndef BOOK_H_
#define BOOK_H_

#include <iostream>
#include <string>
#include "person.h"

using namespace std;

class Book {
private:
	string title;
	Person author;
	string language;
	int year;

	ostream & _print(ostream &);

public:
	Book();
	Book(string, Person, string, int);

	void init(string, Person, string, int);

	// Setters
	void setTitle(string t) { title = t; }
	void setAuthor(Person p) { author = p; }
	void setLanguage(string l) { language = l; }
	void setYear(int y) { year = y; }
	
	// Getters
	string getTitle() { return title; }
	Person getAuthor() { return author; }
	string getLanguage() { return language; }
	int getYear() { return year; }
	
	void print(ostream &);
	
	friend ostream & operator<<(ostream &, Book &); // operator<< cannot be member function
};

#endif