#include "date.h"
#include "person.h"
#include <fstream>

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

int binarySearch(Person p_arr[], int first, int last, Person &targetP) {
	int pos, mid;
	
	while (first < last) {
		mid = (first + last) / 2;
		if (targetP.compare(p_arr[mid]) == 0) return mid + 1;
		else if (targetP.compare(p_arr[mid]) < 0) last = mid - 1;
		else first = mid + 1; 
	}

	if (first == last) 
		pos = (targetP.compare(p_arr[first]) < 0) ? first : first+1;
	else // first > last 
		pos = first; 
	
	return pos;
}		
		
void selectionSort(Person p[], const int size) {
	Person p_min;
	int pos;
	for (int i = 0; i < size; i++) {
		p_min = p[i]; pos = i;
		for (int j = i+1; j < size; j++) {
			if (p_min.compare(p[j]) > 0) {
				p_min = p[j];
				pos = j;
			}
		}
		if (p_min.compare(p[i]) != 0) swap(p[i], p[pos]);
	}	
}

void insertionSort(Person p[], const int size) {
	for (int i = 1; i < size; i++) {
		int pos = binarySearch(p, 0, i-1, p[i]);
		if (pos == i) break;
		Person temp = p[i];
		for (int j = i; j > pos; j--) {
			p[j] = p[j-1];
		}
		p[pos] = temp;
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

int main() {
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
	int arr_size = 1000;
	Person person_array[arr_size];
	int readNum = readData("database1.txt", person_array, arr_size); 
	cout << "Array size: " << arr_size << endl;
	cout << "Read-in person number: " << readNum << endl; 	
	for (int i = 0; i < readNum; i++) {
		cout << "==Person No." << i+1 << ":========" << endl;
		person_array[i].print(cout);
	}
	
	// Part 2
	int test_arr_size = 10;
	Person test_arr[test_arr_size];
	for (int i = 0; i < test_arr_size; i++) {
		test_arr[i] = person_array[i];
	}
	for (int i = 0; i < test_arr_size; i++) {
		cout << "==Person No." << i+1 << ":========" << endl;
		test_arr[i].print(cout);
	}
	selectionSort(test_arr, test_arr_size);
	for (int i = 0; i < test_arr_size; i++) {
		cout << "After Selection Sort" << endl;
		cout << "==Person No." << i+1 << ":========" << endl;
		test_arr[i].print(cout);
	}
	for (int i = 0; i < test_arr_size; i++) {
		test_arr[i] = person_array[i];
	}
	insertionSort(test_arr, test_arr_size);
	for (int i = 0; i < test_arr_size; i++) {
		cout << "After Insertion Sort" << endl;
		cout << "==Person No." << i+1 << ":========" << endl;
		test_arr[i].print(cout);
	}
	for (int i = 0; i < test_arr_size; i++) {
		test_arr[i] = person_array[i];
	}
	bubbleSort(test_arr, test_arr_size);
	for (int i = 0; i < test_arr_size; i++) {
		cout << "After Bubble Sort" << endl;
		cout << "==Person No." << i+1 << ":========" << endl;
		test_arr[i].print(cout);

	}
}

