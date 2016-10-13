#ifndef PR150OBS_H
#define PR150OBS_H

#include <string>
#include <vector>
using namespace std;

class course {
public:
	course();
	~course();
	void schedit();
	bool schedcheck();
	void puttaglist(int x);
	vector<int> gettaglist();
	void putid(string s);
	string getid();
	void putsec(string s);
	string getsec();
	void putprof(string s);
	string getprof();
	void putdow(string s);
	string getdow();
	void putbegtime(string s);
	string getbegtime();
	void putendtime(string s);
	string getendtime();
	void putterm(string s);
	string getterm();
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

#endif
