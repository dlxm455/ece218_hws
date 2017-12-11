#include "bTree.h"
#include "tqueue.h" 

using namespace std;

bnode :: bnode() {
	left = NULL;
	right = NULL;
}

bnode :: bnode(Mstring &s) {
	data = s;
	left = NULL;
	right = NULL;
}

bnode :: ~bnode() { }

bnode * BTree :: _addString(bnode *r, Mstring &s) {
	if (r == NULL) {
		bnode * nb = new bnode(s);
		count++;
		return nb;
	}
	else {
		if (s.compareToIgnoreCase(r->data) < 0) {
			r->left = _addString(r->left, s);
		} else if (s.compareToIgnoreCase(r->data) > 0) {
			r->right = _addString(r->right, s);
		}
		return r;
	}
}

void BTree :: _clearNodePostOrder(bnode *r) {
	if (r != NULL) {
		_clearNodePostOrder(r->left);
		_clearNodePostOrder(r->right);
		delete r; // when node is destroyed, Mstring destructor will be called
		count -= 1;
	}
}

void BTree :: _clear() { // post order
	_clearNodePostOrder(root);
}

void BTree :: _printInOrder(bnode *r, ostream &out) {
	if (r != NULL) {
		_printInOrder(r->left, out);
		r->data.print(out);
		_printInOrder(r->right, out);
	}
}

BTree :: BTree() {
	root = NULL;
	count = 0;	
}

BTree :: ~BTree() {
	_clear();
}

int BTree :: _getHeight(bnode *r) {
	if (r == NULL) return 0;
	else {
		int lh = _getHeight(r->left);
		int rh = _getHeight(r->right);
		int h = (lh > rh) ? lh : rh;
		return h + 1;
	}
}

int BTree :: getHeight() {
	return _getHeight(root);
}

int BTree :: getCount() {
	return count;
}

int BTree :: addString(Mstring &s) {
	root =_addString(root, s);
	return count;
}

ostream& BTree :: print(ostream &out) {
	_printInOrder(root, out);
	return out;
}

// extra credits
void BTree :: _printPreOrder(bnode *r, ostream &out) {
	if (r != NULL) {
		r->data.print(out);
		_printPreOrder(r->left, out);
		_printPreOrder(r->right, out);
	}
}

ostream& BTree :: printPreOrder(ostream &out) {
	_printPreOrder(root, out);
	return out;
}

ostream& BTree :: printBreathFirst(ostream &out) {
	if (root == NULL) return out;
	Tqueue<bnode *> q;
	q.enqueue(root);
	bnode* temp_node = new bnode();
	while(q.getSize() != 0) {
		q.dequeue(temp_node);
		temp_node->data.print(out);
		if (temp_node->left != NULL) q.enqueue(temp_node->left);
		if (temp_node->right != NULL) q.enqueue(temp_node->right);
	}

	return out;

}

