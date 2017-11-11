#ifndef TSTACK_H_
#define TSTACK_H_

#include<iostream>

using namespace std;

template <typename T> 
struct tnode {
	T data;
	tnode<T> * next;
	
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
	int pop(T &);
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
tnode<T> :: ~tnode() {
    next = NULL;
	
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
    
    // delete node one by one from top
	while (trav != NULL) {
		top = top->next;
        
		delete trav; // node destructor is called
        
		trav = top;
	}
    
	size = 0;
}	

template <typename T> 
ostream& Tstack<T>::print(ostream& out) {
	tnode<T> * trav;
	trav = top;
    
    // print one by one from top
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
int Tstack<T> :: pop(T & data) {
    
    // check if stack is empty
	if (top == NULL) {
		fprintf(stderr, "Try to pop from an empty stack.");
		return 1;
	}
	
    // new node pointer to top
	tnode<T> *temp;
	temp = top;
    
	top = top->next; // update top
	data = temp->data; // data returns through parameter

	delete temp; // node destructor is called

	size--; // update size

	return 0;
}

#endif	
