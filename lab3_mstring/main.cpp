#include <iostream>
#include "Mstring.h"
#include <fstream>
#include <string>

using namespace std;

int readFile(Mstring &filename, Mstring *arr, int size) {
	string line;
	char * fn = filename.getString();
	ifstream myfile (fn); // open file
	int count = 0;
	if (myfile.is_open()) {
		while (getline(myfile,line) && count < size) { // get string from each line
			arr[count].setString((char*)line.c_str(), line.size());
			count++; // count number of lines read in
		}
	}
	myfile.close();
	return count;
}

void selectionSort(Mstring p[], const int size) {
	int i, j, min_pos;
	for (i = 0; i < size - 1; i++) {
		min_pos = i;
		for (j = i+1; j < size; j++) {
			if (p[min_pos].compareToIgnoreCase(p[j]) > 0) {
				min_pos = j;
			}
		}
		if (i != min_pos) { // swap, deep copy by overloading "="
			Mstring temp;
			temp = p[i];
			p[i] = p[min_pos];
			p[min_pos] = temp;
		}
	}	
}

int main() {
	/* 1. Create a dynamic Mstring array */

	int arr_size = 100000;
	Mstring * Mstring_arr = new Mstring[arr_size];




	/* 2. Read file function */

	Mstring filename;
	char fn[] = "data1.txt";
	filename.setString(fn, 9);

	int num_line = readFile(filename, Mstring_arr, arr_size);
	cout << " Read in number of lines: " << num_line << endl;



	/* 3. Replace "the" with "over" */
	
	Mstring s, r;
	s.setString((char*)("the"), 3);
	r.setString((char*)("over"), 4);

	int findCount = 0;
	for (int i = 0; i < num_line; i++) {
		if (Mstring_arr[i].findAndReplace(s, r)) 
			findCount++;
	}

	cout << " Find and replace number: " << findCount << endl;



	/* 4. Sort the array of Mstring */

	clock_t start_c = clock();
	selectionSort(Mstring_arr, num_line);
	clock_t end_c = clock();
	double time_ms = (double) (end_c - start_c) / CLOCKS_PER_SEC * 1000.0;
	cout << " Sorting time in ms: " << time_ms << endl;


	
	/* 5. Write the sorted array to a file */
	
	ofstream fout ("sorted_data1.txt");
	if (fout.is_open()) {
		for (int i = 0; i < num_line; i++) {
			Mstring_arr[i].print(fout);
		}
	}
	fout.close();



	/* 6. new array, append, sort */
	int new_arr_size = 50000;
	Mstring * new_arr = new Mstring[new_arr_size];

	// reload Mystring_arr
	num_line = readFile(filename, Mstring_arr, arr_size);

	for (int i = 0; i < new_arr_size; i++) {
		new_arr[i].setString(Mstring_arr[i]);
		new_arr[i].append(Mstring_arr[i+new_arr_size]);
	} 
	
  start_c = clock();
	selectionSort(new_arr, new_arr_size);
	end_c = clock();
	time_ms = (double) (end_c - start_c) / CLOCKS_PER_SEC * 1000.0;
	cout << " New array sorting time in ms: " << time_ms << endl;
	
	fout.open("sorted_new_arr.txt");
	if (fout.is_open()) {
		for (int i = 0; i < new_arr_size; i++) {
			new_arr[i].print(fout);
		}
	}
	fout.close();
}

 