#ifndef PSTACK_H_
#define PSTACK_H_

#include <iostream>
#include "MObject.h"

using namespace std;

struct node {
	MObject * data;
	node * next;

	node();
	virtual ~node();
};

class Pstack {
private:
	node *top;
	int size;

public:
	Pstack();
	virtual ~Pstack();

	ostream& print(ostream&);

	void push(MObject *);
	MObject * pop();
    
    int getSize() { return size; }
};

#endif

