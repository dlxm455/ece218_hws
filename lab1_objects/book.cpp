#include "book.h"

Book::Book() {
	Person p;
	init("NONE", p, "NONE", -1);
}

Book::Book(string t, Person a, string l, int y) {
	init(t, a, l, y);
}

void Book::init(string t, Person a, string l, int y) {
	setTitle(t);
	setAuthor(a);
	setLanguage(l);
	setYear(y);
}

ostream & Book::_print(ostream &out) {
	out << title << endl;
	out << author.getName() << endl;
	out << language << endl;
	out << year << endl;
	return out;
}

void Book::print(ostream &out) {
	out << "==Book=================\n";
	out << "Title: " << title << endl;
	out << "Author: " << author.getName() << endl;
	out << "Language: " << language << endl;
	out << "Year: " << year << endl;
	out << "=======================\n";
}

ostream & operator<<(ostream &out, Book &b) {
	return b._print(out);
}
