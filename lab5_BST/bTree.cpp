#include "bTree.h"
//#include "tqueue.h" 
#include <queue>

using namespace std;

bnode :: bnode() {
	left = NULL;
	right = NULL;
}

bnode :: ~bnode() { }

bnode * BTree :: _addString(bnode *r, Mstring &s) {
	bnode * nb = (bnode *) new bnode();
	if (r == NULL) {
		r = nb;
	}
	else {
		if (s.compareToIgnoreCase(r->data) < 0) {
			r->left = _addString(r->left, s);
		} else {
			r->right = _addString(r->right, s);
		}
	}
	count += 1;
	return r;
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
	_addString(root, s);
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
	queue<bnode *> q;
	q.push(root);
	bnode* temp_node;
	while(!q.empty()) {
		temp_node = q.front();
		temp_node->data.print(out);
		q.pop(); // dequeue
		if (temp_node->left != NULL) q.push(temp_node->left); // enqueue
		if (temp_node->right != NULL) q.push(temp_node->right); // enqueue
	}

	return out;

}

