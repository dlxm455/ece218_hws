#ifndef DLINK_H_
#define DLINK_H_

#include <iostream>
#include <string>

using namespace std;

struct dl_node {
	string data;
	dl_node * prev;
	dl_node * next;
	
	dl_node() { data = ""; prev = NULL; next = NULL; };
	dl_node(string s) { data = s; prev = NULL; next = NULL; };
	
};

class Dlink {
private:
	dl_node * head;
	dl_node * tail;
	int size;

public:	
	Dlink();
	virtual ~Dlink();
	ostream& print(ostream&);
	ostream& printr(ostream&);
	int insert(string s);
};

#endif
