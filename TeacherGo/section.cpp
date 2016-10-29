#include "section.h"
using namespace std;

course::course()
{
    scheduled = false;
}

course::course(string cn="", string mj="", string sn="", string fn="", string ln="", string st="07:00", string et="08:00", string da="11111", string te="0", int u=3)
{
    className = cn;
    major = mj;
    sectionNum = sn;
    firstName = fn;
    lastName = ln;
    startTime = st;
    endTime = et;
    days = da;
    term = te;
    scheduled = false;
    units = u;
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

string course::getClassName()
{
    return className;
}

string course::getDays()
{
    return days;
}

string course::getFirstName()
{
    return firstName;
}

string course::getLastName()
{
    return lastName;
}

string course::getMajor()
{
    return major;
}

string course::getSectNum()
{
    return sectionNum;
}

string course::getStartTime()
{
    return startTime;
}

string course::getEndTime()
{
    return endTime;
}

string course::getTerm()
{
    return term;
}

int course::getUnits()
{
    return units;
}

// Displays days in a more human readabl string
string course::getReadableDays()
{
    string s = "";

    if (days[0] == '1')
        s += "M";
    if (days[1] == '1')
        s += "Tu";
    if (days[2] == '1')
        s += "W";
    if (days[3] == '1')
        s += "Th";
    if (days[4] == '1')
        s += "F";

    return s;
}

void course::setClassName(string n)
{
    className = n;
}

void course::setMajor(string m)
{
    major = m;
}

void course::setSectNum(string n)
{
    sectionNum = n;
}

void course::setFirstName(string n)
{
    firstName = n;
}

void course::setLastName(string n)
{
    lastName = n;
}

void course::setStartTime(string t)
{
    startTime = t;
}

void course::setEndTime(string t)
{
    endTime = t;
}

void course::setDays(string d)
{
    days = d;
}

void course::setTerm(string t)
{
    term = t;
}

void course::setUnits(int u)
{
    units = u;
}

string course::toString()
{
    return sectionNum + "*" + major + "*" + className + "*" + lastName + "*" + firstName + "*" + startTime + "*" + endTime + "*" + days + "*" + term + "*" + std::to_string(units) + "*";
}

