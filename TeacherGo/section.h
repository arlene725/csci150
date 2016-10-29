#ifndef SECTION_H
#define SECTION_H
#include <string>
#include <vector>
using namespace std;

class course
{
public:
    course();
    course(string, string, string, string, string, string, string, string, string, int);
    ~course();
    void schedit();
    bool schedcheck();
    void puttaglist(int x);
    vector<int> gettaglist();

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
    string getReadableDays();
    void setDays(string);
    string getStartTime();
    void setStartTime(string);
    string getEndTime();
    void setEndTime(string);
    string getTerm();
    void setTerm(string);
    int getUnits();
    void setUnits(int);

    string toString();
    friend std::ostream& operator<<(std::ostream&, const course&);

private:
    bool scheduled;
    vector<int> taglist;
    string className;
    string major;
    string sectionNum;
    string firstName;
    string lastName;
    string startTime;
    string endTime;
    string days;
    string term;
    int units;
};
#endif // SECTION_H
