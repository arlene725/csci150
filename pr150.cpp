#include <iostream>
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class course {
public:
	course() { scheduled = false; }
	~course() { delete this; }
	void schedit() { scheduled = true; }
	bool schedcheck() { return scheduled; }
	void puttaglist(int x) { taglist.push_back(x); }
	vector<int> gettaglist() { return taglist; }
	void putid(string s) { cid = s; }
	string getid() { return cid; }
	void putsec(string s) { sec = s; }
	string getsec() { return sec; }
	void putprof(string s) { prof = s; }
	string getprof() { return prof; }
	void putdow(string s) { dow = s; }
	string getdow() { return dow; }
	void putbegtime(string s) { begtime = s; }
	string getbegtime() { return begtime; }
	void putendtime(string s) { endtime = s; }
	string getendtime() { return endtime; }
	void putterm(string s) { term = s; }
	string getterm() { return term; }
private:
	bool        scheduled;
	vector<int> taglist;
	string      cid;
	string      sec;
	string      prof;
	string      dow;
	string      begtime;
	string      endtime;
	string      term;
};

vector<course*> added;
vector<course*> possibles;

void initobj(string s, course * o);
bool canadd(course * a, course * b);
double minconv(int x);
double dectime(string s);
int getit(double x);

int main(int argc, char *argv[]) {
	ifstream insched;
	ofstream outsched;
	string parse;
	course * c;
	insched.open("scheduleadd.txt");
	if (!insched.is_open()) {
		cout << "Unable to open file.\n";
		exit(EXIT_FAILURE);
	}
	while (!EOF) {
		getline(insched, parse);
		c = new course();
		initobj(parse, c);
		possibles.push_back(c);

	}
	if (possibles.at(0)->schedcheck() == false)
		cout << "false" << endl;
	char f;
	cin >> f;

	return 0;
}

void initobj(string s, course * o) {
	string put;
	int i = 0;
	int j;
	while (s.at(i) != '*') {
		put.push_back(s.at(i));
		++i;
	}
	++i;
	o->putid(put);
	put.clear();
	while (s.at(i) != '*') {
		put.push_back(s.at(i));
		++i;
	}
	++i;
	o->putsec(put);
	put.clear();
	while (s.at(i) != '*') {
		put.push_back(s.at(i));
		++i;
	}
	++i;
	o->putprof(put);
	put.clear();
	while (s.at(i) != '*') {
		put.push_back(s.at(i));
		++i;
	}
	++i;
	o->putdow(put);
	put.clear();
	while (s.at(i) != '*') {
		put.push_back(s.at(i));
		++i;
	}
	++i;
	o->putbegtime(put);
	put.clear();
	while (s.at(i) != '*') {
		put.push_back(s.at(i));
		++i;
	}
	++i;
	o->putendtime(put);
	put.clear();
	while (s.at(i) != '*') {
		put.push_back(s.at(i));
		++i;
	}
	o->putterm(put);
	i = getit(dectime(o->getbegtime()));
	j = getit(dectime(o->getendtime()));
	while (i <= j) {
		o->puttaglist(i);
		++i;
	}
}

bool canadd(course * a, course *b) {
	string da = a->getdow();
	string db = b->getdow();
	vector<int> ta = a->gettaglist();
	vector<int> tb = b->gettaglist();
	if ((da == db) && (ta == tb))
		return false;
	for (unsigned int i = 0; i < da.size(); ++i) {
		for (unsigned int j = 0; j < db.size(); ++j) {
			if (da.at(i) == db.at(j)) {
				for (unsigned int x = 0; x < ta.size(); ++x) {
					for (unsigned int y = 0; y < tb.size(); ++y) {
						if (da.at(i) == db.at(j))
							return false;
					}
				}
			}
		}
	}
	return true;
}

void addcourse(course * o) {
	o->schedit();
	added.push_back(o);
	return;
}

/**
* MINCONV converts minutes to a decimal value for use in the
* double value that represents time converted to base 10
*/
double minconv(int x) {
	double ans = x / 60.0;
	return ans;
}
/**
* DECTIME iterates through the string, and finds the portrion
* represents the hour first. It will leave that in base 10,
* but it converts it to a double. Next, it will convert the
* minutes portion to an integer value. It will alter the hour
* portion depending on whether or not the time is given as am
* or pm. Once this is done, it feeds the minutes integer into
* the MINCONV function, and appends the decimal to the newly
* created time double, which is returned.
*/
double dectime(string s) {
	double result = 0.0;
	int min = 0;
	int i = 0;
	string substr;
	char c = s.at(i);
	if (s.empty() || (!isdigit(s.at(0)))) {
		cout << "Invalid format\n";
		exit(EXIT_FAILURE);
	}
	while (c != ':') {
		substr += c;
		++i;
		c = s.at(i);
	}
	result += stod(substr);
	substr.clear();
	++i;
	c = s.at(i);
	while (isdigit(s.at(i))) {
		substr += c;
		++i;
		c = s.at(i);
	}
	min = stoi(substr);
	while (iswspace(s.at(i)))
		++i;
	if (s.at(i) == 'p') {
		if (result != 12.0)
			result += 12.0;
	}
	else if (s.at(i) == 'a') {
		if (result == 12.0)
			result = 0.0;
	}
	else {
		cout << "Invalid format\n";
		exit(EXIT_FAILURE);
	}
	result += minconv(min);
	return result;
}

/**
* GETIT will take the time double generated from DECTIME and
* use it to generate an iterator which will be used to populate
* the data structure for the schedule, allowing for detection
* of time conflicts.
*/
int getit(double x) {
	int result;
	double test = floor(x);
	result = static_cast<int>(test) * 2;
	if ((x - test) > 0.0)
		result += 1;
	return result;
}