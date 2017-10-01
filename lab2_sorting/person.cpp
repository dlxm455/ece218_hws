#include "person.h"

Person::Person() {
	Date d; d.init(0);
	init(0, "NONE", "NONE", d);	
}

Person::Person(string ssn_str, string fN, string lN, string b_str) {
	Date d; d.init(atoi(b_str.c_str()));
	init(atoi(ssn_str.c_str()), fN, lN, d);
}

void Person::print(ostream & out) {
	out << "==Person==========" << endl;
	out << "SSN: " << getSSN() << endl;
	out << "First Name: " << getFirstName() << endl;
	out << "Last Name: " << getLastName() << endl;
	Date b = getBirthday();
	out << "Birthday: "; 
	b.print(out);
}

int Person::compare(Person & p) {
	string s1 = getLastName();
	string s2 = p.getLastName();
	int cmp_res = s1.compare(s2);
	if (cmp_res < 0) return -1;
	else if (cmp_res == 0) return 0;
	else return 1; 
}

