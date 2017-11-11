#include "pstack.h"

using namespace std;

node :: node() {
	data = NULL;
	next = NULL;
}

node :: ~node() {
	if (data != NULL) {
		next = NULL;
        
		delete data; // MObject destructor is called
		data = NULL;
	}
	//cout << "node destructs" << endl;
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
		delete trav; // node destructor is called
		trav = top;
	}
		size = 0;
    //cout << "stack destructs" << endl;
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
    
    // set new node
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

	// unlink temp from the next
	temp->next = NULL;
    
    // set return MObject pointer
	MObject * ret = temp->data;
    
    // unlink data which is needed for return
	temp->data = NULL;
    
	delete temp; //  node destructor is called
    
	return ret;
}


 
