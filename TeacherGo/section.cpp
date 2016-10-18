#include "section.h"
#include <string>
using std::string;

section::section(string cn="", string mj="", string sn="", string fn="", string ln="", string st="07:00", string et="08:00", string da="MtuWThF", int te=0)
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
}

string section::getClassName()
{
    return className;
}

string section::getDays()
{
    return days;
}

string section::getFirstName()
{
    return firstName;
}

string section::getLastName()
{
    return lastName;
}

string section::getMajor()
{
    return major;
}

string section::getSectNum()
{
    return sectionNum;
}

string section::getStartTime()
{
    return startTime;
}

string section::getEndTime()
{
    return endTime;
}

int section::getTerm()
{
    return term;
}


void section::setClassName(string n)
{
    className = n;
}

void section::setMajor(string m)
{
    major = m;
}

void section::setSectNum(string n)
{
    sectionNum = n;
}

void section::setFirstName(string n)
{
    firstName = n;
}

void section::setLastName(string n)
{
    lastName = n;
}

void section::setStartTime(string t)
{
    startTime = t;
}

void section::setEndTime(string t)
{
    endTime = t;
}

void section::setDays(string d)
{
    days = d;
}

void section::setTerm(int t)
{
    term = t;
}

string section::toString()
{
    return sectionNum + "*" + major + "*" + className + "*" + firstName + "*" + lastName + "*" + startTime + "*" + endTime + "*" + days + "*" + std::to_string(term);
}

