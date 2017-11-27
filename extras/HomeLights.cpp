#include "HomeLights.h"
#include <iostream>
#include <string>

using namespace std;

ostream& light :: print(ostream &out) {
	out << "location: " << location << ", " << "state: ";
	if (onState) out << "on\n";
	else out << "off\n";
	return out;
}

lnode :: lnode() {
	data = NULL;
	next = NULL;
}

lnode :: ~lnode() {
	if (data) delete data;
	data = NULL;
	next = NULL;
}

HomeLights :: HomeLights() {
	head = NULL;
	tail = NULL;
	count = 0;
}

HomeLights :: ~HomeLights() {
	lnode * trav = head;
	if (head != NULL) {
		trav = head;
		delete trav;
		head = head->next;
	}
	tail = NULL;
	count = 9;
}

int HomeLights :: addALight(string loc) {
	light * l = new light(); // Will this work even no constructor
	l->location = loc;
	l->onState = false;
	
	lnode * n = new lnode();
	n->data = l;
	
	if (count == 0) {
		head = n;
		tail = n;
	}
	else if (loc.compare(head->data->location) <= 0) {
		n->next = head;
		head = n;
	}
	else if (loc.compare(tail->data->location) >= 0) {
		tail->next = n;
		tail = n;
	}
	else {
		lnode * trav = head;
		lnode * trav_pre = NULL;
		while (loc.compare(trav->data->location) > 0) {
			trav_pre = trav;
			trav = trav->next;
		}
		trav_pre->next = n;
		n->next = trav;
	}

	count++;
	return count;
}


int HomeLights :: removeLight(string loc) {
	// if linked list is empty
	if (count == 0) {
		return 0;
	}

	lnode * trav = head;
	lnode * trav_pre = NULL;
	// find the position
	while (trav != NULL && loc.compare(trav->data->location) != 0) {
		trav_pre = trav;
		trav = trav->next;
	}
	// not found
	if (trav == NULL) {
		printf("%s is not found\n", loc.c_str());
		return count;
	}
	// delete all equal nodes
	while (loc.compare(trav->data->location) == 0) {
		// need a pointer to hold the next before deleting
		// either head or trav_pre->next 
		if (head == trav) {
			head = trav->next;
			delete trav;
			trav = head;
		}
		else {
			trav_pre->next = trav->next;
			delete trav;
			trav = trav_pre->next;
		}
		count--;
		if (trav == NULL) {
			tail = NULL;
			break;
		}
	}
	return count;
}


bool HomeLights :: getLightState(string loc) {
	lnode * trav = head;
	while (trav != NULL && loc.compare(trav->data->location) != 0) {
		trav = trav->next;
	}
	if (trav != NULL) {
		return trav->data->onState;
	}
	else {
		fprintf(stderr, "no lights at %s  location\n", loc.c_str());
		exit(1);
	}
	return false;
}

void HomeLights :: setStateTo(string loc, bool s) {
	lnode * trav = head;
	while (trav != NULL && loc.compare(trav->data->location) != 0) {
		trav = trav->next;
	}

	if (trav == NULL) { // not find
		printf("no lights at %s location\n", loc.c_str());
		return;
	}
	// find all
	while (trav != NULL && loc.compare(trav->data->location) == 0) {
		trav->data->onState = s;
		trav = trav->next;
	}

}

int HomeLights :: setAll(bool s) {
	lnode * trav = head;
	int trav_count = 0;
	while (trav != NULL) {
		trav->data->onState = s;
		trav = trav->next;
		trav_count++;;
	}
	return trav_count;
}

ostream& HomeLights :: print(ostream &out) {
	lnode * trav = head;
	while (trav != NULL) {
		trav->data->print(out);
		trav = trav->next;
	}
	return out;
}



HomeLights_vec :: HomeLights_vec() {
	ptr_light = NULL;
	count = 0;
}

HomeLights_vec :: ~HomeLights_vec() {
	if (ptr_light) delete[] ptr_light;
	count = 0;
}

int HomeLights_vec :: addALight(string loc) {
	int add_ind = 0;
	// find where to add
	while (add_ind < count && loc.compare(ptr_light[add_ind].location) > 0) {
		add_ind++;
	}

	light * new_ptr = new light[count + 1];
	// is onState false?
	for (int i = 0; i < add_ind; i++) {
		// will '=' work for struct
		new_ptr[i] = ptr_light[i];
	}
	new_ptr[add_ind].location = loc;
	new_ptr[add_ind].onState = false;

	for (int i = add_ind; i < count; i++) {
		new_ptr[i+1] = ptr_light[i];
	}

	delete[] ptr_light;
	ptr_light = new_ptr;
	count++;
	return count;
}

int HomeLights_vec :: removeLight(string loc) {
	int del_start_ind;
	int del_end_ind;
	int i = 0;
	while (i < count && loc.compare(ptr_light[i].location) != 0) {
		i++;
	}
	if (i == count) {
		printf("no light at %s\n", loc.c_str());
		return count;
	}
	del_start_ind = i;
	while (i < count && loc.compare(ptr_light[i].location) == 0) {
		i++;
	}
	del_end_ind = i - 1;
	light * new_ptr = new light[count + del_start_ind - del_end_ind - 1];
	for (i = 0; i < del_start_ind; i++) {
		new_ptr[i] = ptr_light[i];
	}
	for (i = del_end_ind + 1; i < count; i++) {
		new_ptr[i + del_start_ind - del_end_ind - 1] = ptr_light[i];
	}

	return del_end_ind - del_start_ind + 1;
}

bool HomeLights_vec :: getLightState(string loc) {
	int i = 0;
	while(i < count && loc.compare(ptr_light[i].location) != 0) {
		i++;
	}
	if (i == count) {
		printf("no lights at %s\n", loc.c_str());
		return false;
	}
	return ptr_light[i].onState;
}

void HomeLights_vec :: setStateTo(string loc, bool s) {
	int i = 0;
	while (i < count && loc.compare(ptr_light[i].location) != 0) {
		i++;
	}
	if (i == count) {
		printf("no lights at %s\n", loc.c_str());
		return;
	}
	while (i < count && loc.compare(ptr_light[i].location) == 0) {
		ptr_light[i].onState = s;
		i++;
	}
}

int HomeLights_vec :: setAll(bool s) {
	int i;
	for (i = 0; i < count; i++) {
		ptr_light[i].onState = s;
	}
	return i;
}

ostream& HomeLights_vec :: print(ostream& out) {
	for (int i = 0; i < count; i++) {
		ptr_light[i].print(out);
	}
	return out;
}

