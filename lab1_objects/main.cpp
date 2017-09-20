#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "person.h"
#include "book.h"
#include "library.h"

using namespace std;


int readData(string fname, Book b[], const int size, bool reverse = false) {
	ifstream fin(fname.c_str());
	if (fin.fail()) return -1;

	int i = 0;
	string t, an, l, ystr;
	int y;

	while (i < size) {
		if (!getline(fin, t)) break;
		if (!getline(fin, an)) break;
		if (!getline(fin, l)) break;
		if (!getline(fin, ystr)) break;
		Person p;
		p.setName(an);
		y = atoi(ystr.c_str());
		if (!reverse)
			b[i].init(t, p, l, y);
		else
			b[size - 1 - i].init(t, p, l, y);
		i++;
	}
	fin.close();
	return i;
}



int writeData(string fname, Book b[], const int size) {
	ofstream fout(fname.c_str());
	if (fout.fail()) return -1;
	int i;
	for (i = 0; i < size; i++) {
		if (fout.fail()) break;
		fout << b[i];
	}
	fout.close();
	return i;
}


void printArray(Book b[], const int size) {
	for (int i = 0; i < size; i++) {
		cout << b[i];
	}
}

void reverseArray(Book b[], const int size) {
	Book temp;
	for (int i = 0; i < size / 2; i++) {
		temp = b[i];
		b[i] = b[size - 1 - i];
		b[size - 1 - i] = temp;
	}
}

int main() {
	cout << "Program started\n";

	// Ex 1
	Person me;
	me.print(cout);
	
	me.setName("Shijia Geng");
	me.print(cout);

	// Ex 2
	Book my_book;
	my_book.print(cout);

	my_book.init("Amazing", me, "Chinese", 2005);
	my_book.print(cout);

	// Ex 3
	/*
	Book my_books[46];
	int nread = readData("Book2Mac.txt", my_books, 46);
	printArray(my_books, nread);
	reverseArray(my_books, nread);
	
	Book my_reverse_books[46];
	nread = readData("Book2Mac.txt", my_reverse_books, 46, true);
	reverseArray(my_reverse_books, nread);
	int nwrite = writeData("testBooks.txt", my_reverse_books, nread);i
	
	cout << "==Check if two files are the same==\n";
	int compareRes = system("diff -w testBooks.txt", "Book2Mac.txt");
	if (!compareRes) cout << "The two files are the same." << endl; 
	else cout << "The two files are not the same." << endl;
	*/
	// Ex 4
	Library my_library;
	my_library.setName("Shijia's Library");
	my_library.setOwner(me);
	my_library.print(cout);
	int errNo = my_library.setBooks("Book2Mac.txt", 46);
	if (errNo == -1) 
		cout << "Library is not loaded." << endl;
	else if (errNo != 0)
		cout << "Only" << errNo << " number of books are loaded." << endl;
	my_library.print(cout);
	cout << "Program ended\n";
	return 0;
}