#include "date.h"
#include "person.h"

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
	
	

}

