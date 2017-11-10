#include "pstack.h"

using namespace std;

node :: node() {
	data = NULL;
	next = NULL;
}

node :: ~node() {
	if (data != NULL) {
		next = NULL;
		delete data;
		data = NULL;
	}
	cout << "destruct node" << endl;
}

Pstack :: Pstack() {
	top = NULL;
	size = 0;
}

Pstack :: ~Pstack() {
	node * trav;
	trav = top;
	while (trav != NULL) {
		top = top->next;
		delete trav; // call the node destructor
		trav = top;
	}
		size = 0;
    cout << "destruct stack" << endl;
}

ostream& Pstack :: print(ostream& out) {
	node * trav;
	trav = top;
	while (trav != NULL) {
		(trav->data)->print(out) << ' ';
		trav = trav->next;
	}
	out << endl;
	return out;
}

void Pstack :: push(MObject * mo) {
	// create node
	node * n = new node;
	n->data = mo;
	n->next = top;
	
	// update stack
	top = n;
	size++;
}

MObject * Pstack :: pop() {
	if (top == NULL) return NULL;
	
	// make a node pointer point to top
	node * temp;
	temp = top;

	//update list
	top = top->next;
	size--;

	// unlink temp, delete temp, return temp data
	temp->next = NULL;
	MObject * ret = temp->data;
	temp->data = NULL;
	delete temp; // call node destructor
	return ret;
}


 
