#ifndef MSTRING_H_
#define MSTRING_H_

#include <iostream>
using namespace std;

class Mstring {
private:
	char *str;
	int length;
	bool compareStartInd(int Ind, Mstring &s);
public:
	Mstring();
	~Mstring();
	void setString(char*, int);
	void setString(Mstring &s);
	char * getString();
	char charAt(int loc);
	int append(char*, int);
	int append(Mstring &s);
	bool findAndReplace(Mstring &s, Mstring &r);
	int compareToIgnoreCase(Mstring &s);
	ostream &print(ostream &out);
	Mstring &operator=(Mstring &b) {
		this->setString(b);
		return *this;
	}
};
	


#endif
