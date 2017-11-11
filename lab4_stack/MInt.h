#ifndef MINT_H_
#define MINT_H_

#include <iostream>
#include "MObject.h"

using namespace std;

class MInt : public MObject {
public:
	MInt() { value = NULL; };
	MInt(int i) { int* ni = new int(i); setValue((void *)ni); }; // alternative constructor
    virtual ~MInt() { if (value != NULL) { delete (int*)value; value = NULL;} };
	//int getValue() { return (int)*value_ptr; };
	
	ostream& print(ostream& out) { out << *(int*)getValue(); return out; };
};

#endif

