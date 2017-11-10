#ifndef TSTACK_H_
#define TSTACK_H_

#include<iostream>

using namespace std;

template <typename T> 
struct tnode {
	T data;
	tnode<T> * next; // do i need <> 
	
	tnode(); // default constructor
	tnode(T d); // alternative constructor
	~tnode(); // destructor
};


template <typename T>
class Tstack {
private:
	tnode<T> * top;
	int size;

public:
	Tstack();
	virtual ~Tstack();
	ostream& print(ostream&);
	void push(T data);
	T pop();
};



// Implement of tnode
template <typename T>
tnode<T> :: tnode() { 
	data = NULL;
	next = NULL;
}

template <typename T>
tnode<T> :: tnode(T d) { // alternative destructor
	data = d; 
	next = NULL;
}

template <typename T>
tnode<T> :: ~tnode() { // TODO
	
}



// Implement of Tstack
template <typename T>
Tstack<T>::Tstack() {
	top = NULL;
	size = 0;
}

template <typename T>
Tstack<T>::~Tstack() {
	tnode<T> *trav;
	trav = top;
	while (trav != NULL) {
		top = top->next;
        
        // delete trav
		trav->next = NULL; 
		delete trav;
        
		trav = top;
	}
	size = 0;
}	

template <typename T> 
ostream& Tstack<T>::print(ostream& out) {
	tnode<T> * trav;
	trav = top;
	while (trav != NULL) {
		out<< trav->data << ' ';
		trav = trav->next;
	}
	out << endl;

	return out;
}
	
template <typename T> 
void Tstack<T> :: push(T data) {
    // create new node
	tnode<T> *n = new tnode<T>(data);
    // connect node to list
	n->next = top;
    
    // update list
	top = n;
	size++;
}

template <typename T> 
T Tstack<T> :: pop() {
	if (top == NULL) {
		fprintf(stderr, "Cannot pop from an empty stack.");
		exit(1);
	}
	
	tnode<T> *temp;
	temp = top;
	top = top->next;
	T ret = temp->data;

	// delete temp
	temp -> next = NULL;
	delete temp;

	size--;

	return ret;
}

#endif	
