#include "date.h"
#include "person.h"
#include <fstream>
#include <iostream>
#include <string>

int readData(string fname, Person p[], const int size) {	
	ifstream fin(fname.c_str());
	if (fin.fail()) return -1;
	int i;
	string ssnStr, fName, lName, dobStr;
	Date d;
	
	for (i = 0; i < size; i++) { 
		fin >> ssnStr >> fName >> lName >> dobStr;
		if (fin.fail()) break;
		d.init(atoi(dobStr.c_str()));
		p[i].init(atoi(ssnStr.c_str()), fName, lName, d);
	} 
	return i;
}


void swap(Person &p1, Person &p2) {
	Person temp = p1;
	p1 = p2;
	p2 = temp; 
}

int binarySearch(Person p_arr[], int first, int last, int targetInd) {
	int pos = targetInd;
	int mid;
	Person targetP = p_arr[targetInd];
	while (first <= last) {
		if (targetP.compare(p_arr[first]) < 0) return first;
		else if (targetP.compare(p_arr[last]) > 0 || targetP.compare(p_arr[last]) == 0) return last+1;

		mid = (first + last) / 2;
		if (targetP.compare(p_arr[mid]) < 0) last = mid - 1;
		else first = mid + 1; 
	}

	return pos;
}		
		
void selectionSort(Person p[], const int size) {
	int i, j, min_pos;
	for (i = 0; i < size - 1; i++) {
		min_pos = i;
		for (j = i+1; j < size; j++) {
			if (p[min_pos].compare(p[j]) > 0) {
				min_pos = j;
			}
		}
		if (i != min_pos) swap(p[i], p[min_pos]);
	}	
}

void insertionSort(Person p[], const int size) {
	for (int i = 1; i < size; i++) {
		int pos = binarySearch(p, 0, i-1, i);
		if (pos != i) { 
			Person temp = p[i];
			for (int j = i; j > pos; j--) {
				p[j] = p[j-1];
			}
			p[pos] = temp;
		}
	}		 
}

void bubbleSort(Person p[], const int size) {
	for (int i = size - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (p[j].compare(p[j+1]) > 0)
				swap(p[j], p[j+1]);
		}
	}
}  

int main(int argc, char * argv[]) {
	if (argc < 2) { 
		cerr << "Database file is required" << endl;
		exit(1);
	}
	
	
	// part1 1
	cout << "Program started" << endl;
	Date d;
	int fD = 19920528; 
	d.init(fD);
	d.print(cout);
	
	Person p1;
	p1.print(cout);
	p1.init(222334444, "Jerry", "BBB", d);
	p1.print(cout);

	Person p2("111223333", "Tom", "AAA", d.getFormattedString());
	p2.print(cout);
	
	int cmp_res = p1.compare(p2);
	if (cmp_res == 0) {
		cout << "p1 and p2 have same last name" << endl;
	}
	else {
		Person p_small = (cmp_res < 0) ? p1 : p2;
		cout << p_small.getFirstName() << " "
			<< p_small.getLastName() 
			<< " has \'smaller\' last name" << endl;
	}
	cout << "Program ended" << endl;
	// find array size from the file name; assume file name format is database(n).txt
	int digit_num = 0;
	char c = argv[1][8];
	while (c != '.') {
		digit_num += 1;
		c = argv[1][8+digit_num];
	}
	char arr_size_arr[digit_num+1];
	for (int i = 0; i < digit_num; i++) {
		arr_size_arr[i] = argv[1][8+i];
	}
	arr_size_arr[digit_num] = '\0'; 
	int arr_size = atoi(arr_size_arr) * 1000; 
	Person person_array[arr_size];

	int readNum = readData(argv[1], person_array, arr_size); 
	cout << "Array size: " << arr_size << endl;
	/*
	cout << "Read-in person number: " << readNum << endl; 	
	for (int i = 0; i < readNum; i++) {
		cout << "==Person No." << i+1 << ":========" << endl;
		person_array[i].print(cout);
	}
	*/ 
	// Part 2
	
	int test_arr_size = arr_size;
	Person test_arr[test_arr_size];
	for (int i = 0; i < test_arr_size; i++) {
		test_arr[i] = person_array[i];
	}
	/*
	for (int i = 0; i < test_arr_size; i++) {
		cout << "==Person No." << i+1 << ":========" << endl;
		test_arr[i].print(cout);
	}
	*/
	clock_t start_select = clock();
	selectionSort(test_arr, test_arr_size);
	clock_t end_select = clock();
	double time_select = (double)(end_select- start_select);
	
	cout << "====== After Selection Sort ======" << endl;
	for (int i = 0; i < 10; i++) {
		cout << "==Person No." << i+1 << ":========" << endl;
		//test_arr[i].print(cout);
		cout << test_arr[i].getLastName() << endl;
	}

	for (int i = 0; i < test_arr_size; i++) {
		test_arr[i] = person_array[i];
	}
	
	clock_t start_insert = clock();
	insertionSort(test_arr, test_arr_size);
	clock_t end_insert = clock();
	double time_insert = (double) (end_insert -  start_insert);
	
	cout << "====== After Insertion Sort ======" << endl;
	for (int i = 0; i < 10; i++) {
		cout << "==Person No." << i+1 << ":========" << endl;
		//test_arr[i].print(cout);
		cout << test_arr[i].getLastName() << endl;
	}
	
	for (int i = 0; i < test_arr_size; i++) {
		test_arr[i] = person_array[i];
	}
	clock_t start_bubble = clock();
	bubbleSort(test_arr, test_arr_size);
	clock_t end_bubble = clock();
	double time_bubble = (double)(end_bubble - start_bubble);
	
	cout << "====== After Bubble Sort ======" << endl;
	for (int i = 0; i < 10; i++) {
		cout << "==Person No." << i+1 << ":========" << endl;
		//test_arr[i].print(cout);
		cout << test_arr[i].getLastName() << endl;

	}
	
	cout << "SelectionSort time: " << time_select << endl;
	cout << "InsertionSort time: " << time_insert << endl;
	cout << "BubbleSort time: " << time_bubble << endl;
}

