#include "person.h"

// Default constructor

Person::Person() {
	Date d; d.init(0); // set all attributes of the date as 0
	init(0, "NONE", "NONE", d); // set the person's ssn as 0, names as "NONE"	
}



// Alternative constructor: set attributes as given values

Person::Person(string ssn_str, string fN, string lN, string b_str) {
	Date d; d.init(atoi(b_str.c_str()));
	init(atoi(ssn_str.c_str()), fN, lN, d);
}



// Print the person's attributes

void Person::print(ostream & out) {
	out << "==Person==========" << endl;
	out << "SSN: " << getSSN() << endl;
	out << "First Name: " << getFirstName() << endl;
	out << "Last Name: " << getLastName() << endl;
	Date b = getBirthday();
	out << "Birthday: "; 
	b.print(out);
}



// Compare this person's last name with the parameter person's one
// '<' means in front in alphabetical order, '>' means behind 
// return -1, if this person's last name '<' parameter person's 
// return 0, if they are the same
// return 1, if this person's last name '>' parameter person's 

int Person::compare(Person & p) {
	string s1 = getLastName();
	string s2 = p.getLastName();
	int cmp_res = s1.compare(s2);

	if (cmp_res < 0) return -1;
	else if (cmp_res == 0) return 0;
	else return 1; 
}


