#include <iostream>
#include <string>
#include "dlink.h"

using namespace std;

Dlink :: Dlink() {
	head  = NULL;
	tail = NULL;
	size = 0;
}

Dlink :: ~Dlink() {
	dl_node * trav;
	trav = head;
	while (head != NULL) {
		trav = head;
		head = head->next;
		delete trav;
	}
	tail = NULL;
	size = 0;
}


ostream& Dlink :: print(ostream& out) {
	dl_node * trav;
	trav = head;
	while (trav != NULL) {
		out << trav->data << endl;
		trav = trav->next;
	}
	return out;
}

ostream& Dlink :: printr(ostream& out) {
	dl_node * trav;
	trav = tail;
	while (trav != NULL) {
		out << trav->data << endl;
		trav = trav->prev;
	}
	return out;
}

int Dlink :: insert(string s) {

	dl_node * n = new dl_node(s);
	
	if (size == 0) {
		head = n;
		tail = n;
;
	}
	else if (s.compare(head->data) <= 0) {
		// add to head
		n->next = head;
		head->prev = n;
		head = n;
	}
	
	else if (s.compare(tail->data) >= 0) {
		// add to tail
		n->prev = tail;
		tail->next = n;
		tail = n;
	}

	else {
		dl_node *trav;
		trav = head;
		while (s.compare(trav->data) > 0) {
			trav = trav->next;
		}
		trav->prev->next = n;
		n->next = trav;
		n->prev = trav->prev;
		trav->prev = n;
	} 

	size++;
	return size;
}
