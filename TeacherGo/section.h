#ifndef SECTION_H
#define SECTION_H
#include <string>
using std::string;

class section
{
public:
    section(string, string, string, string, string, string, string, string, int);
    string getClassName();
    void setClassName(string);
    string getMajor();
    void setMajor(string);
    string getSectNum();
    void setSectNum(string);
    string getFirstName();
    void setFirstName(string);
    string getLastName();
    void setLastName(string);
    string getDays();
    void setDays(string);
    string getStartTime();
    void setStartTime(string);
    string getEndTime();
    void setEndTime(string);
    int getTerm();
    void setTerm(int);

    string toString();
    friend std::ostream& operator<<(std::ostream&, const section&);

private:
    string className;
    string major;
    string sectionNum;
    string firstName;
    string lastName;
    string startTime;
    string endTime;
    string days;
    int term;
};
#endif // SECTION_H
