#include "person.h"

Person::Person() {
	setName("NONE");
}

void Person::print(ostream &out) {
	out << "==Person===============\n";
	out << "Name: " << name << endl;
	out << "=======================\n";
}
