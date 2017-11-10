#ifndef MOBJECT_H_
#define MOBJECT_H_

#include <iostream>

using namespace std;

class MObject {
protected:
	void * value;

public:
	MObject() { value = NULL; };
    virtual ~MObject() { if (value != NULL) value = NULL; cout << "destruct mobject" << endl;};

	virtual void setValue(void * v) { value = v; };
	virtual void * getValue() { return value; };

	virtual ostream& print(ostream&) = 0;
};

#endif

