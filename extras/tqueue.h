#include<iostream>
/*
template <typename T>
struct tnode {
	T * data_ptr;
	tnode * next;
	
	tnode();
	tnode(T);
	~tnode();
	
};
*/

template <typename T>
class Tqueue {
private:
	tnode<T> * front;
	tnode<T> * back;
	int size;
	void _print(tnode<T> * n, ostream&);

public:
	Tqueue();
	virtual ~Tqueue();
	void enqueue(T);
	int dequeue(T&);
	ostream& print(ostream&);
    int getSize();

};

/*
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
		next = NULL;
 }
}
*/

template <typename T>
Tqueue<T> :: Tqueue() {
	front = NULL;
	back = NULL;
	size = 0;
}
template <typename T>
Tqueue<T> :: ~Tqueue() {
	tnode<T> * trav;
	while (back != NULL) {
		trav = back;
		back = back->next;
		delete trav;
	}
	front = NULL;
	size = 0;
}

template <typename T>
void Tqueue<T> :: enqueue(T data) {
	tnode<T> * temp = new tnode<T>(data);
	if (front == NULL) 
		front = temp;
	temp->next = back;
	back = temp;
	size++;	
	
} 

template <typename T>
int Tqueue<T> :: dequeue(T& data) {
	if (size == 0) {
		fprintf(stderr, "Queue is empty. Nothing to dequeue.\n");
		return 1;
	}

	if (size == 1) {
		data = *(front->data_ptr);
		delete front;
		front = NULL;
		back = NULL;
		size = 0;
		return 0;
	}

	tnode<T> * trav;
	trav = back;
		
	while (trav->next != front) {
		trav = trav->next;
	}
	data = *(front->data_ptr);
	delete front;
	front = trav;
	size --;

	return 0;
}

template <typename T>
void Tqueue<T> :: _print(tnode<T> * n, ostream& out) {
	if (n != NULL) {
		_print(n->next, out);
		out << *(n->data_ptr) << " ";
	}
}	

template <typename T>
ostream& Tqueue<T> :: print(ostream &out) {
	_print(back, out);
	out << endl;
	return out;	
}

template <typename T>
int Tqueue<T> :: getSize() {
    return size;
}

