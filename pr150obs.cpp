#include "pr150obs.h"
using namespace std;

course::course() {
	scheduled = false;
}

course::~course() {
	delete this;
}

void course::schedit() {
	scheduled = true;
	return;
}

bool course::schedcheck() {
	return scheduled;
}

void course::puttaglist(int x) {
	taglist.push_back(x);
	return;
}

vector<int> course::gettaglist() {
	return taglist;
}

void course::putid(string s) {
	cid = s;
	return;
}

string course::getid() {
	return this->cid;
}

void course::putsec(string s) {
	this->sec = s;
	return;
}

string course::getsec() {
	return this->sec;
}

void course::putprof(string s) {
	this->prof = s;
	return;
}

string course::getprof() {
	return this->prof;
}

void course::putdow(string s) {
	this->dow = s;
	return;
}

string course::getdow() {
	return this->dow;
}

void course::putbegtime(string s) {
	this->begtime = s;
	return;
}

string course::getbegtime() {
	return this->begtime;
}

void course::putendtime(string s) {
	this->endtime = s;
	return;
}

string course::getendtime() {
	return this->endtime;
}

void course::putterm(string s) {
	this->term = s;
	return;
}

string course::getterm() {
	return this->term;
}