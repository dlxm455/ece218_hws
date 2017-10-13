#include "date.h"
#include "person.h"
#include <fstream>
#include <iostream>
#include <string>

// Part 1.3: Fuction to read the data from a file to fill Person array  
int readData(string fname, Person p[], const int size) {	
	ifstream fin(fname.c_str());
	if (fin.fail()) return -1;
	int i;
	string ssnStr, fName, lName, dobStr;
	Date d;
	
	for (i = 0; i < size; i++) { 
		fin >> ssnStr >> fName >> lName >> dobStr;
		if (fin.fail()) break;
		d.init(atoi(dobStr.c_str())); //set date 
		p[i].init(atoi(ssnStr.c_str()), fName, lName, d); // set person
	} 
	return i;
}



// swap function
void swap(Person &p1, Person &p2) {
	Person temp = p1;
	p1 = p2;
	p2 = temp; 
}



// Binary search function for binaryInsertionSort (not demonstrate in this assignment)
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



// Selection sort function
void selectionSort(Person p[], const int size) {
	int i, j, min_pos;
	for (i = 0; i < size - 1; i++) {
		min_pos = i;
		for (j = i+1; j < size; j++) {
			if (p[min_pos].compare(p[j]) > 0) {
				min_pos = j;
			}
		}
		if (i != min_pos) { // did not use swap function here to keep consistent with insertion sort
			Person temp = p[i];
			p[i] = p[min_pos];
			p[min_pos] = temp;
		}
	}	
}



// Insertion sort using binary search (not demonstrate in this assignment)
void binaryInsertionSort(Person p[], const int size) {
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



// Ordinary insertion sort not using binary search
void insertionSort(Person p[], const int size) {
	for (int i = 1; i < size; i++) {
		int pos = i;
		for (int j = 0; j < i; j++) {
			if (p[j].compare(p[i]) > 0) {
				pos = j;
				break; // break when find the position to insert
			}
		}
		if (pos != i) {
			// 'long' swap
			Person temp = p[i];
			for (int j = i; j > pos; j--) {
				p[j] = p[j-1];
			}
			p[pos] = temp;
		}
	}
}



// Bubble sort
void bubbleSort(Person p[], const int size) {
	for (int i = size - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (p[j].compare(p[j+1]) > 0)
				swap(p[j], p[j+1]);
		}
	}
} 



// Copy arr1 from arr2 with given size
void copyArr(Person arr1[], Person arr2[], const int size) {
	for (int i = 0; i < size; i++) {
		arr1[i] = arr2[i];
	}
}


// Reverse an array
void reverseArr(Person arr[], const int size) {
	for (int i = 0; i < size / 2; i++) {
		swap(arr[i], arr[size - 1 - i]);
	}
}   



// Print a given number of last names from a Person array
void printTest(Person test_arr[], const int size) {
	for (int i = 0; i < size; i++) {
		cout << "==Person No." << i+1 << ":========" << endl;
		//test_arr[i].print(cout);
		cout << test_arr[i].getLastName() << endl;
	}
}



int main(int argc, char * argv[]) {

	// Make sure input database file is provided
	if (argc < 2) { 
		cerr << "Database file is required" << endl;
		exit(1);
	}
	
	
	cout << "Program started" << endl;


	/* Part1: Basic Objects and Functions */
 
	// Part 1.1 Test date class
	Date d;
	int fD = 19920528; 
	d.init(fD);
	cout << "==Date========" << endl;
	d.print(cout);

	// Part 1.2 Test person class
	Person p1; // test default constructor
	p1.print(cout);
	p1.init(222334444, "Jerry", "BBB", d); // test setter
	p1.print(cout);

	Person p2("111223333", "Tom", "AAA", d.getFormattedString()); // test alternative constructor
	p2.print(cout);
	
	int cmp_res = p1.compare(p2); // test compare function
	if (cmp_res == 0) {
		cout << "p1 and p2 have same last name" << endl;
	}
	else {
		Person p_small = (cmp_res < 0) ? p1 : p2;
		cout << p_small.getFirstName() << " "
			<< p_small.getLastName() 
			<< " has \'smaller\' last name" << endl;
	}
	
	cout << " " <<endl;
	
	// Part 1.5 Make array number adjusted with the file name
 	
	// Find out array size from the file name, assume file name format is database?.txt
	int digit_num = 0; // number of digits in ?
	char c = argv[1][8]; // character after 'database'
	while (c != '.') { // find out how many digits in ?
		digit_num += 1;
		c = argv[1][8+digit_num];
	}

	char arr_size_arr[digit_num+1]; // create a c string to hold ? 

	for (int i = 0; i < digit_num; i++) {
		arr_size_arr[i] = argv[1][8+i];
	}
	arr_size_arr[digit_num] = '\0'; 
	
	int arr_size = atoi(arr_size_arr) * 1000; // find out number of data entries
	cout << "Size of data entries: " << arr_size << endl;



	// Part 1.4 Test readData function

	// Create a person array with the data entries size in the given file 
	Person person_array[arr_size];

	int readNum = readData(argv[1], person_array, arr_size); 
	
	// Print out Person array
	/*
	cout << "Read-in person number: " << readNum << endl; 	
	for (int i = 0; i < readNum; i++) {
		cout << "==Person No." << i+1 << ":========" << endl;
		person_array[i].print(cout);
	}
	*/
	
	/* Part 2: Sorting unsorted data */
	cout << "======== Sorting unsorted data ========" << endl;
	// Create a test array 		
	int test_arr_size = arr_size;
	Person test_arr[test_arr_size];
	
	// Selection sort
	copyArr(test_arr, person_array, test_arr_size); // copy from person array
	//printTest(test_arr, 10); // to check the first 10 last names in the test array
	
	clock_t start_select = clock();
	selectionSort(test_arr, test_arr_size);
	clock_t end_select = clock();
	double time_select = (double)(end_select- start_select);
	
	cout << "====== After Selection Sort ======" << endl;
	printTest(test_arr, 10);



	// Insertion sort	
	copyArr(test_arr, person_array, test_arr_size); // reset test array
	
	clock_t start_insert = clock();
	insertionSort(test_arr, test_arr_size);
	clock_t end_insert = clock();
	double time_insert = (double) (end_insert -  start_insert);
	
	cout << "====== After Insertion Sort ======" << endl;
	printTest(test_arr, 10);



	// Bubble sort
	copyArr(test_arr, person_array, test_arr_size); // reset test array

	clock_t start_bubble = clock();
	bubbleSort(test_arr, test_arr_size);
	clock_t end_bubble = clock();
	double time_bubble = (double)(end_bubble - start_bubble);
	
	cout << "====== After Bubble Sort ======" << endl;
	printTest(test_arr, 10);
	
	cout << "SelectionSort time: " << time_select << endl;
	cout << "InsertionSort time: " << time_insert << endl;
	cout << "BubbleSort time: " << time_bubble << endl;



	/* Part3 Sorting sorted data */

	cout << "======== Sorting sorted array =========" << endl;
	//printTest(test_arr,10);

	start_select = clock();
	selectionSort(test_arr, test_arr_size);
	end_select = clock();
	time_select = (double)(end_select - start_select);

	start_insert = clock();
	insertionSort(test_arr, test_arr_size);
	end_insert = clock();
	time_insert = (double)(end_insert -  start_insert);
	
	start_bubble = clock();
	bubbleSort(test_arr, test_arr_size);
	end_bubble = clock();
	time_bubble = (double)(end_bubble - start_bubble);

	cout << "SelectionSort time for sorted array: " << time_select << endl;
	cout << "InsertionSort time for sorted array: " << time_insert << endl;
	cout << "BubbleSort time for sorted array: " << time_bubble << endl;


	cout << "========= Sorting reversed array =========" << endl;

	reverseArr(test_arr, test_arr_size);
	//printTest(test_arr, 20);
	start_select = clock();
	selectionSort(test_arr, test_arr_size);
	end_select = clock();
	time_select = (double)(end_select- start_select);

	reverseArr(test_arr, test_arr_size);
	start_insert = clock();
	insertionSort(test_arr, test_arr_size);
	end_insert = clock();
	time_insert = (double)(end_insert -  start_insert);
	
	reverseArr(test_arr, test_arr_size);
	start_bubble = clock();
	bubbleSort(test_arr, test_arr_size);
	end_bubble = clock();
	time_bubble = (double)(end_bubble - start_bubble);

	cout << "SelectionSort time for reversed array: " << time_select << endl;
	cout << "InsertionSort time for reversed array: " << time_insert << endl;
	cout << "BubbleSort time for reversed array: " << time_bubble << endl;
	
	cout << "Program ended." << endl;
}

