#include <iostream>
#include <fstream>
#include "tstack.h"
#include <string>
#include "tqueue.h"
#include "dlink.h"
#include "HomeLights.h"

using namespace std;

int loadDataToArr(char * fname, string string_arr[], int arr_size) {
	// open data file
	ifstream fin;
	fin.open(fname);

	// load data to dynamic array
	string str_input;
	int i = 0;
	while (getline(fin, str_input)) {
		string_arr[i] = str_input;
		i++;
	}

	// close data file
	fin.close();

	return i;
}

void selectionSort(string p[], const int size) {
	int i, j, min_pos;
	for (i = 0; i < size - 1; i++) {
		min_pos = i;
		for (j = i+1; j < size; j++) {
			if (p[min_pos].compare(p[j]) > 0) {
				min_pos = j;
			}
		}
		if (i != min_pos) {
			// swap
			string temp;
			temp = p[i];
			p[i] = p[min_pos];
			p[min_pos] = temp;
		}
	}	
}

void insertionSort(string p[], const int size) {
	for (int i = 1; i < size; i++) {
		int pos = i;
		for (int j = 0; j < i; j++) {
			if (p[j].compare(p[i]) > 0) {
				pos = j;
				break;
			}
		}
		if (pos != i) {
			// 'long' swap
			string temp = p[i];
			for (int j = i; j > pos; j--) {
				p[j] = p[j-1];
			}
			p[pos] = temp;
		}
	}
}

void bubbleSort(string p[], const int size) {
	for (int i = size - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (p[j].compare(p[j+1]) > 0) {
				// swap
				string temp;
				temp = p[j];
				p[j] = p[j+1];
				p[j+1] = temp;
			}
		}
	}
}

int main() {

	// 1.
	cout << "===== Question 1 =====" << endl;
	Tstack<char>  s1;
	cout << "Please enter a line of text:" << endl;
	char input[256] = "";
	scanf("%s", input);
	int i = 0;
	while (input[i] != '\0') {
		s1.push(input[i]);
		i++;
	}
	s1.print(cout);



	//2.
	cout << "===== Question 2 =====" << endl;
	Tqueue<string> q1;
	string str1 = "string1";
	string str2 = "string2";
	string str3 = "string3";

	q1.enqueue(str1);
	cout << "Enqueue element: " << str1 << endl;
	q1.enqueue(str2);
	cout << "Enqueue element: " << str2 << endl;
	q1.enqueue(str3);
	cout << "Enqueue element: " << str3 << endl;

	cout << "Elements in queue:";
	q1.print(cout);

	string dstr1;
	string dstr2;
	string dstr3;

	q1.dequeue(dstr1);
	cout << "Deqeue element: " << dstr1 << endl;
	q1.dequeue(dstr2);
	cout << "Deqeue element: " << dstr2 << endl;
	q1.dequeue(dstr3);
	cout << "Deqeue element: " << dstr3 << endl;



	// 3.
	cout << "===== Question 3 =====" << endl;
	Dlink dl;
	string str4 = "string4";
	string str5 = "string5";

	dl.insert(str3);
	dl.insert(str5);
	dl.insert(str1);
	dl.insert(str4);
	dl.insert(str2);

	cout << "Print double link from head to tail." << endl;
	dl.print(cout);
	cout << "Print double link from tail to head." << endl;
	dl.printr(cout);



	// 4.
	cout << "===== Question 4 =====" << endl;
/*
	Dlink * dl2 = new Dlink();

	// load data to dynamic array
	int arr_size = 100000;
	string * string_arr = new string[arr_size];

	char datafile[] = "/tmp/data1.txt";
	int ret_load = loadDataToArr(datafile, string_arr, arr_size);

	if (ret_load != arr_size) {
		fprintf(stderr, "read data failed\n");
		exit(1);
	}

	// insert to double link and timing
	clock_t start_c = clock();
	int i;
	for (i = 0; i < arr_size; i++) {
		dl2->insert(string_arr[i]);
	}
	clock_t end_c = clock();
	double time_ms = (double) (end_c - start_c) / CLOCKS_PER_SEC * 1000.0;
	cout << "Double link insertion time in ms: " << time_ms << endl;

	// write double link contents to file
	ofstream fout;
	fout.open("sorted_data1_dl.txt");
	dl2->print(fout);
	fout.close();

	// delete double link
	delete dl2;


	// selection sort and timing
	start_c = clock();
	selectionSort(string_arr, arr_size);
	end_c = clock();
	time_ms = (double) (end_c - start_c) / CLOCKS_PER_SEC * 1000.0;
	cout << "Selection sort  time in ms: " << time_ms << endl;

	// write selection sort results to file
	fout.open("sorted_data1_selection.txt");
	for (i = 0; i < arr_size; i++) {
		fout << string_arr[i] << endl;
	}
	fout.close();



	// reload arr
	ret_load = loadDataToArr(datafile, string_arr, arr_size);
	if (ret_load != arr_size) {
		fprintf(stderr, "read data failed\n");
		exit(1);
	}

	// insertion sort and timing
	start_c = clock();
	insertionSort(string_arr, arr_size);
	end_c = clock();
	time_ms = (double) (end_c - start_c) / CLOCKS_PER_SEC * 1000.0;
	cout << "Insertion sort  time in ms: " << time_ms << endl;

	// write insertion sort results to file
	fout.open("sorted_data1_insertion.txt");
	for (i = 0; i < arr_size; i++) {
		fout << string_arr[i] << endl;
	}
	fout.close();



	// reload arr
	ret_load = loadDataToArr(datafile, string_arr, arr_size);
	if (ret_load != arr_size) {
		fprintf(stderr, "read data failed\n");
		exit(1);
	}

	// bubble sort and timing
	start_c = clock();
	bubbleSort(string_arr, arr_size);
	end_c = clock();
	time_ms = (double) (end_c - start_c) / CLOCKS_PER_SEC * 1000.0;
	cout << "Bubble sort  time in ms: " << time_ms << endl;

	// write bubble sort results to file
	fout.open("sorted_data1_bubble.txt");
	for (i = 0; i < arr_size; i++) {
		fout << string_arr[i] << endl;
	}
	fout.close();
	
	// delete dynamic array
	delete[] string_arr;


*/
	// 5.
	cout << "===== Question 5 =====" << endl;
	HomeLights * hl = new HomeLights();

	int add_i = 5;
	while (add_i--) {
		hl->addALight("living_room"); // is this ok. string literal to string
	}
	
	add_i = 2;
	while (add_i--) {
		hl->addALight("bedroom1");
	}

	add_i = 2;
	while (add_i--) {
		hl->addALight("bedroom2");
	}

	hl->addALight("kitchen");

	hl->setStateTo("living_room", true);
	hl->setStateTo("bedroom1", true);

	hl->print(cout);

	delete hl;

	// 6.
	cout << "===== Question 6 =====" << endl;
	HomeLights_vec * hlv = new HomeLights_vec();
	
	add_i = 5;
	while (add_i--) {
		hlv->addALight("living_room");
	}
	
	add_i = 2;
	while (add_i--) {
		hlv->addALight("bedroom1");
	}

	add_i = 2;
	while (add_i--) {
		hlv->addALight("bedroom2");
	}

	hlv->addALight("kitchen");

	hlv->setStateTo("living_room", true);
	hlv->setStateTo("bedroom1", true);

	hlv->print(cout);

	delete hlv;
	
	return 0;
}

