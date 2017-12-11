#include <iostream>
#include <fstream>
#include <sys/time.h>
#include <sys/resource.h>
#include <math.h>
#include <string>
#include "bTree.h"
#include "Mstring.h"

using namespace std;


double getCPUTime(void) {
    struct timeval tv;
    struct rusage ru;
    getrusage(RUSAGE_SELF, &ru);
    tv = ru.ru_utime;
    double t = (double)tv.tv_sec + (double)tv.tv_usec/1000000.0;
    tv = ru.ru_stime;
    t += (double)tv.tv_sec + (double)tv.tv_usec/1000000.0;
    return t;
}


int readFile(Mstring &filename, Mstring *arr, int size) {
	ifstream fin;
	fin.open(filename.getString());
	if (!fin.is_open()) {
		fprintf(stderr, "open file failed.\n");
		exit(1);
	}

	char str[128]; 
	int i = 0;
	while (fin.getline(str, 128) && i < size) {
		arr[i].setString(str, strlen(str));
		i++;
	}

	fin.close();
	return i;
}

void selectionSort(Mstring p[], const int size) {
	int i, j, min_pos;
	for (i = 0; i < size; i++) {

		// find the position where has the minimum element 
		min_pos = i;
		for (j = i + 1; j < size; j++) {
			if (p[j].compareToIgnoreCase(p[min_pos]) < 0) {
				min_pos = j;
			}
		}

		// swap
		if (i != min_pos) {
			Mstring temp;
			temp = p[i];
			p[i] = p[min_pos];
			p[min_pos] = temp;
		}

	}
}

int main() {

	// 1. Create a dynamic array of Mstring of size 100000
	int arr_size = 10; //100000;
	Mstring * arr = new Mstring[arr_size];

	// 2. Call function to fill in the arr from a file
	Mstring filename_ms;
	char fn[] = "testdata.txt"; //"data1.txt";
	filename_ms.setString(fn, strlen(fn));
	int read_num = readFile(filename_ms, arr, arr_size);
	if (read_num != arr_size) {
		fprintf(stderr, "not all strings are read in array.\n");
		exit(1);
	}
	cout << "arr: " << endl;
	for (int i = 0; i < arr_size; i++) {
		arr[i].print(cout);
	}
	cout << endl;
	// 3. Create and populate a dynamic BTree
	BTree * bt = new BTree();
	double starttime = getCPUTime();
	for (int i = 0; i < arr_size; i++) {
		bt->addString(arr[i]);
	}
	cout << "tree inorder: " << endl;
	bt->print(cout);
	cout << endl;

	cout << "tree breathfirst: " << endl;
	bt->printBreathFirst(cout);
	cout << endl;

	double endtime = getCPUTime();
	double elapsetime = endtime - starttime;
	cout << "Time to create BTree from unsorted array: ";
	cout << elapsetime << " sec" << endl; 
	int h = bt->getHeight();
	cout << "Height of BTree built from unsorted array: " << h << endl;

	// 4. Sort the array of Mstring
	double starttime_s = getCPUTime();
	selectionSort(arr, arr_size);
	double endtime_s = getCPUTime();
	double elapsetime_s = endtime_s - starttime_s;
	cout << "Time to sort array: " << elapsetime_s << " sec" << endl;
	

	// 5. Create and populate a second dynamic BTree
	BTree *bt2 = new BTree();
	double starttime_tree_s = getCPUTime();
	for (int i = 0; i < arr_size; i++) {
		bt2->addString(arr[i]);
	}
	double endtime_tree_s = getCPUTime();
	double elapsetime_tree_s = endtime_tree_s - starttime_tree_s;
	cout << "Time to create BTree from sorted array: ";
	cout << elapsetime_tree_s << " sec" << endl; 
	int h_s = bt2->getHeight();
	cout << "Height of BTree built from sorted array: " << h_s << endl;

	// calculate the idea height
	// h >= log2(N+1)
	int h_ideal = (int)ceil(log(arr_size + 1) / log(2));
	cout << "Ideal Height: " << h_ideal << endl; 

	// 6. Compare the resulting times	
	// TODO

	// Extra Credit
	// write tree to file with pre-order
	ofstream fout;
	fout.open("preOrderFile.txt");
	bt->printPreOrder(fout);
	fout.close();

	// read file back to arr;
	char fn2[] = "preOrderFile.txt";
	filename_ms.setString(fn2, strlen(fn2));
	int read_num2 = readFile(filename_ms, arr, arr_size);
	if (read_num2 != arr_size) {
		fprintf(stderr, "not all strings are read in array.\n");
		exit(1);
	}

	// create and populate a new BTree from the arr
	BTree *bt3 = new BTree();
	double starttime_newtree = getCPUTime();
	for (int i = 0; i < arr_size; i++) {
		bt3->addString(arr[i]);
	}
	double endtime_newtree = getCPUTime();
	double elapsetime_newtree = endtime_newtree - starttime_newtree;
	cout << "Time to create BTree from preorder rebuild array: ";
	cout << elapsetime_newtree << " sec" << endl; 
	int h_n = bt3->getHeight();
	cout << "Height of BTree built from preorder rebuild array: ";
	cout << h_n << endl;

	// TODO comment
	// TODO comment4	
	// delete Mstring array
	delete[] arr;
	
	// delete BTrees
	delete bt;
	delete bt2;
	delete bt3;


}
