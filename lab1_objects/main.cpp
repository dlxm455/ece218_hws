#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "person.h"
#include "book.h"
#include "library.h"

using namespace std;

#ifndef bookNum
#define bookNum 46
#endif


// Read information from a text file and set a Book array.
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


// Write information of each element from a Book array to a file.
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

// Print each element of a Book array.
void printArray(Book b[], const int size) {
	for (int i = 0; i < size; i++) {
		b[i].print(cout);
	}
}

// Reverse the order of a Book array.  
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
	Book my_books[bookNum];
	int nread = readData("Book2Mac.txt", my_books, bookNum);
    cout << "==Print out all the books in the array===\n";
	printArray(my_books, nread);
    cout << "=========================================\n";
    
	reverseArray(my_books, nread);
    cout << "==Print out all the books in the array after being reversed===\n";
    printArray(my_books, nread);
    cout << "==============================================================\n";
	
	Book my_reverse_books[bookNum];
    // pass reverse parameter as true to set the array in reverse order
	nread = readData("Book2Mac.txt", my_reverse_books, bookNum, true);
    // reverse the array which is set in reverse order
	reverseArray(my_reverse_books, nread);
    // write the result data to "testBooks.txt"
	int nwrite = writeData("testBooks.txt", my_reverse_books, nread);
	
	cout << "==Check if two files are the same==\n";
    // call system function diff to check if the two files are the same
	int compareRes = system("diff -w testBooks.txt Book2Mac.txt");
	if (!compareRes) cout << "The two files are the same." << endl; 
	else cout << "The two files are not the same." << endl;
    cout << "====================================\n";
	
	// Ex 4
	Library my_library;
    my_library.print(cout);
    
	my_library.setName("Awesome Library");
	my_library.setOwner(me);
	
	int errNo = my_library.setBooks("Book2Mac.txt", bookNum);
    // report the setBooks results
	if (errNo == -1) 
		cout << "Library is not loaded." << endl;
	else if (errNo != 0 && errNo < bookNum)
		cout << "Only " << errNo << " number of books are loaded." << endl;
    else
        my_library.print(cout);
	cout << "Program ended\n";
	return 0;
}