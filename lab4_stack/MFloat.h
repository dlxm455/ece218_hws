#ifndef MFloat_H_
#define MFloat_H_

#include <iostream>
#include "MObject.h"

using namespace std;

class MFloat : public MObject {
public:
	MFloat() { value = NULL; };
	MFloat(float i) { float* ni = new float(i); setValue((void *)ni); };
	
	ostream& print(ostream& out) { out << *(float*)getValue(); return out; };
};

#endif
