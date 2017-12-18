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
	fin.open(filename.getString(), ifstream::in);
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

void buildTreeFromSortedArr(BTree * bt, Mstring *arr, int start_ind, int end_ind) {
	if (start_ind <= end_ind) {
		int mid = (end_ind - start_ind) / 2 + start_ind;
		bt->addString(arr[mid]);
		buildTreeFromSortedArr(bt, arr, start_ind, mid - 1);
		buildTreeFromSortedArr(bt, arr, mid + 1, end_ind);
	}
}

// partition version 1
int partition1(Mstring p[], int start_ind, int end_ind) {
	int i = start_ind;
	int j = end_ind - 1;

	while (i < j) {
		while(p[i].compareToIgnoreCase(p[end_ind]) < 0) {
			i++;
		}
		while(j >= start_ind && p[j].compareToIgnoreCase(p[end_ind]) > 0) {
			j--;
		}
		if (i < j && p[i].compareToIgnoreCase(p[j]) != 0) { // swap
			Mstring temp;
			temp = p[i];
			p[i] = p[j];
			p[j] = temp;
		}
	}

	// place pivot
	if (i != end_ind) {
		Mstring temp;
		temp = p[i];
		p[i] = p[end_ind];
		p[end_ind] = temp;
	}

	return i;
}

// partition version 2
int partition2(Mstring p[], int start_ind, int end_ind) {
	int i = start_ind;

	return i;
}

// my quicksort
void myQuicksort(Mstring p[], int start_ind, int end_ind,
								 int (*partition_func)(Mstring *, int, int)) {
	if (start_ind >  end_ind) {
		int p_ind = partition_func(p, start_ind, end_ind);
		myQuicksort(p, start_ind, p_ind - 1, partition_func);
		myQuicksort(p, p_ind + 1, end_ind, partition_func);
	}
}


int main(int argc, char* argv[]) {
	int read_num;
	double starttime, endtime, elapsetime;
	int i;
	
	bool testflag = false;
	if (argc == 0) {
		fprintf(stderr, "please provide data file.\n");
		exit (1);
	}
	//char fn[] = "testdata.txt"; //"data1.txt";

	if (strcmp(argv[1], "testdata.txt") == 0) {
		testflag = true;
	}

	// 1. Create a dynamic array of Mstring of size 100000
	int arr_size = 100000;
	if (testflag) arr_size = 10; 

	Mstring * arr = new Mstring[arr_size];


	// 2. Call function to fill in the arr from a file
	Mstring filename_ms;
	filename_ms.setString(argv[1], strlen(argv[1]));
	read_num = readFile(filename_ms, arr, arr_size);
	if (read_num != arr_size) {
		fprintf(stderr, "not all strings are read in array\n");
		exit(1);
	}
	
	
	// 3. Sort the array with selection sort
	starttime = getCPUTime();
	selectionSort(arr, arr_size);
	endtime = getCPUTime();
	elapsetime = endtime - starttime;
	cout << "Selection sort time: " << elapsetime << " sec" << endl;

	// 4. Save the sorted data to a file
	ofstream fout;
	fout.open("SelectionSortOutput.txt");
	if (!fout.is_open()) {
		fprintf(stderr, "open file failed.\n");
		exit(1);
	}

	for (i = 0; i < arr_size; i++) {
		arr[i].print(fout);
	}

	fout.close();

	// 5. Reload the data
	read_num = readFile(filename_ms, arr, arr_size);
	if (read_num != arr_size) {
		fprintf(stderr, " not all strings are read in array\n");
		exit(1);
	}

	// 6. Sort the array with quicksort
	starttime = getCPUTime();
	myQuicksort(arr, 0, arr_size - 1, partition1);
	endtime = getCPUTime();
	elapsetime = endtime - starttime;
	cout << "Quicksort time: " << elapsetime << " sec" << endl;

	// 7. Save the sorted data to a file
	fout.open("QuickSortOutput.txt");
	if (!fout.is_open()) {
		fprintf(stderr, "open file failed.\n");
		exit(1);
	}

	for (i = 0; i < arr_size; i++) {
		arr[i].print(fout);
	}

	fout.close();

	// 9c. Create and populate a dynamic BTree
	BTree * bt = new BTree();

	starttime = getCPUTime();
	for (i = 0; i < arr_size; i++) {
		bt->addString(arr[i]);
	}
	endtime = getCPUTime();
	elapsetime = endtime - starttime;
	cout << "Time to create BTree from unsorted array: ";
	cout << elapsetime << " sec" << endl; 

	delete[] arr;
	delete bt;

}

