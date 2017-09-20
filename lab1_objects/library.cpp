#include "library.h"

using namespace std;

Library::Library() {
	setName("None");
	Person p;
	setOwner(p);
}

int Library::setBooks(string fname, int size) {
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
		books[i].init(t,p,l,y);
		i++;
	}
	fin.close();
	return i;
}

void Library::print(ostream &out) {
	out << "==Library================\n";
	out << "Name : " << name << endl;
	out << "Owner: " << name << endl;
	out << "Books: " << endl;
	for (int i = 0; i < 46; i++) {
		out << books[i];
	}
	out << "=========================\n";
}