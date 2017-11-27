#include <iostream>
#include <string>

using namespace std;

struct light {
	string location;
	bool onState;

	ostream &print(ostream &out);
};

struct lnode {
	light * data;
	lnode * next;

	lnode();
	virtual ~lnode();
};

class HomeLights {
private:
	lnode *head, *tail;
	int count;
public:
	HomeLights();
	virtual ~HomeLights();
	int addALight(string loc);
	int removeLight(string loc);
	bool getLightState(string loc);
	void setStateTo(string loc, bool s);
	int setAll(bool s);
	ostream &print(ostream &out);
};

class HomeLights_vec {
private:
	light * ptr_light;
	int count;
public:
	HomeLights_vec();
	virtual ~HomeLights_vec();
	int addALight(string loc);
	int removeLight(string loc);
	bool getLightState(string loc);
	void setStateTo(string loc, bool s);
	int setAll(bool s);
	ostream &print(ostream &out);
};

