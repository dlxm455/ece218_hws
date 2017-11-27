#include<iostream>

using namespace std;

template <typename T>
struct tnode {
	T * data_ptr;
	tnode * next;

	tnode();
	tnode(T);
	~tnode();
	
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
	void push(T);
	int pop(T&);
};

template <typename T>
tnode<T> :: tnode() {
	data_ptr = NULL;
	next = NULL;
}

template <typename T>
tnode<T> :: tnode(T data) {
	T * t_ptr = new T(data);
	data_ptr = t_ptr;
	next = NULL;
}

template <typename T>
tnode<T> :: ~tnode() {
	if (data_ptr != NULL) {
		delete data_ptr;
		data_ptr = NULL;
	}
	next = NULL;
}

template <typename T>
Tstack<T> :: Tstack() {
	top = NULL;
	size = 0;
}

template <typename T>
Tstack<T> :: ~Tstack() {
	tnode<T> * trav;
	while (top != NULL) {
		trav = top;
		top = top->next;
		delete trav;
	}
	size = 0;
}

template <typename T>
ostream& Tstack<T> :: print(ostream& out) {
	tnode<T> * trav;
	trav = top;
	while (trav != NULL) {
		out << *(trav->data_ptr) << ' ';
		trav = trav->next;
	}
	out << endl;

	return out;
}

template <typename T>
void Tstack<T> :: push(T data) {
	tnode<T> * n = new tnode<T>(data);
	n->next = top;

	top = n;
	size++;
}

template <typename T>
int  Tstack<T> :: pop(T& data) {
	if (top == NULL) {
		fprintf(stderr, "stack is empty, nothing popped.\n");
		return 1;
	}

	tnode<T> * temp;
	temp = top;

	top = top->next;
	data = *(temp->data_ptr);

	delete temp;
	size--;
	return 0;
}

