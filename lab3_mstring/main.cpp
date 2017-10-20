#include <iostream>
#include "Mstring.h"

using namespace std;

int main() {
	Mstring ms;
	char my_s[] = "the cat and the rat";
	ms.setString(my_s, 19);
	ms.print(cout);
	Mstring s;
	char the[] = "the";
	s.setString(the,3);
	Mstring r;
	char over[] = "over";
	r.setString(over, 4);
	bool find = ms.findAndReplace(s,r);
	if (find) cout << "Find!" << endl;
	else cout << "Not find!" << endl;
	ms.print(cout);

} 