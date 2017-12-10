#ifndef BTREE_H_
#define BTREE_H_

#include<iostream>
#include "Mstring.h"

using namespace std;

struct bnode {
	Mstring data;
	bnode * left;
	bnode * right;
};

class BTree {
private:
	bnode * root;
	int count;

	bnode *_addString(bnode *r, Mstring &s);
	void _clear();
	void _printInOrder(bnode *r, ostream &out);
	void _clearNodePostOrder(bnode *r);
	int _getHeight(bnode *r);

	// extra credits
	void _printPreOrder(bnode *r, ostream &out);

public:
	BTree();
	~BTree();
	int getHeight();
	int getCount();
	int addString(Mstring &s);
	ostream& print(ostream &out); // in order

	// extra credits
	ostream& printPreOrder(ostream &out);
	ostream& printBreathFirst(ostream &out);
};

#endif
