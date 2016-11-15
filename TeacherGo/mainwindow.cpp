#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTime>
#include <QString>
#include <string>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>
#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    classes = 0;
    ui->setupUi(this); // Creates the gui
    connect(ui->actionSave, SIGNAL(triggered(bool)), this, SLOT(save())); // Sets up save menu option
    connect(ui->actionLoad, SIGNAL(triggered(bool)), this, SLOT(load())); // Sets up load menu option
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Saves all the sections in possible vector. Activated when save menu item is triggered.
void MainWindow::save()
{
        QFile file(QFileDialog::getSaveFileName(this, tr("Save courses"), QDir::currentPath(), tr("Data (*dat)")));

        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
                return;
        QTextStream out(&file);
        for(int i = 0;i < classes;i++)
        {
            out << QString::fromStdString(possibles[i]->toString()) << "\n";
        }
}

// Loads sections saved in a file. Overwrites any sections currentyl in possibles. Activated when load menu item is triggered.
void MainWindow::load()
{
    QFile file(QFileDialog::getOpenFileName(this, tr("Load courses"), QDir::currentPath(), tr("Data (*dat)")));

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&file);
    string line;// = in.readLine().toStdString();
    classes = 0;
    ui->sectTable->clearContents();

    course * o;
    while (!in.atEnd())
    {
        line = in.readLine().toStdString();
        o = new course();
        initobj(line, o);
        possibles.push_back(o);
        classes++;
        addToTable(o);
    }
}

//Creates schedule from possibles when button clicked
void MainWindow::on_schedButt_clicked()
{
    bool cAdd;
    if(classes > 0)
    {
        added.clear();
        int totUnits = 0;
        addcourse(possibles[0]);
        totUnits += possibles[0]->getUnits();

        for(int i = 1; i < classes; i++)
        {
            if(possibles[i]->getUnits() + totUnits <= ui->unitsDesBox->value())
            {
                cAdd = true;
                for(int j = 0; j < i; j++)
                {
                    if(!canadd(possibles[j], possibles[i]))
                    {
                        cAdd = false;
                    }
                }
                if (cAdd)
                {
                    addcourse(possibles[i]);
                    totUnits += possibles[i]->getUnits();
                }
            }
        }
    }
    dispSched();
}

// Displays schedule in table.
void MainWindow::dispSched()
{
    course * o;
    ui->schedTable->clearContents();
    for(int i = 0; i < added.size(); i++)
    {
        o = added.at(i);

        if(o->getDays().at(0) == '1')//Monday
        {
            for(int j = 0; j < o->gettaglist().size(); j ++)
            {
                ui->schedTable->setItem(o->gettaglist()[j] - 14,0, new QTableWidgetItem(QString::fromStdString(o->getClassName())));
            }
        }
        if(o->getDays().at(1) == '1')//Tuesday
        {
            for(int j = 0; j < o->gettaglist().size(); j ++)
            {
                ui->schedTable->setItem(o->gettaglist()[j] - 14, 1, new QTableWidgetItem(QString::fromStdString(o->getClassName())));
            }
        }
        if(o->getDays().at(2) == '1')//Wednesday
        {
            for(int j = 0; j < o->gettaglist().size(); j ++)
            {
                ui->schedTable->setItem(o->gettaglist()[j] - 14, 2, new QTableWidgetItem(QString::fromStdString(o->getClassName())));
            }
        }
        if(o->getDays().at(3) == '1')//Thursday
        {
            for(int j = 0; j < o->gettaglist().size(); j ++)
            {
                ui->schedTable->setItem(o->gettaglist()[j] - 14, 3, new QTableWidgetItem(QString::fromStdString(o->getClassName())));
            }
        }
        if(o->getDays().at(4) == '1')//Friday
        {
            for(int j = 0; j < o->gettaglist().size(); j ++)
            {
                ui->schedTable->setItem(o->gettaglist()[j] - 14, 4, new QTableWidgetItem(QString::fromStdString(o->getClassName())));
            }
        }
    }
}

// Processed when submit button is pressed. Does minimal testing on input data and creates new section.
void MainWindow::on_pushButton_clicked()
{
    QMessageBox msg;
    if(ui->classNameBox->text().isEmpty())
    {
        msg.setText("Please enter a class name");
        msg.exec();
    }
    else if(ui->majorBox->currentText().isEmpty())
    {
        msg.setText("Please choose major");
        msg.exec();
    }
    else if(ui->sectionBox->text().isEmpty())
    {
        msg.setText("Please enter section number");
        msg.exec();
    }
    else if(ui->firstNameBox->text().isEmpty() || ui->lastNameBox->text().isEmpty())
    {
        msg.setText("Please enter the professors name");
        msg.exec();
    }
    else if(!ui->monBox->isChecked() && !ui->tuesBox->isChecked() && !ui->wedBox->isChecked() && !ui->thurBox->isChecked() && !ui->friBox->isChecked())
    {
        msg.setText("Please select days the class meets");
        msg.exec();
    }
    else if(ui->startTime->time() >= ui->endTime->time())
    {
        msg.setText("Start time needs to happen before end time");
        msg.exec();
    }
    else
    {
        string classNa = ui->classNameBox->text().toStdString();
        string maj = ui->majorBox->currentText().toStdString();
        string sectN = ui->sectionBox->text().toStdString();
        string fName = ui->firstNameBox->text().toStdString();
        string lName = ui->lastNameBox->text().toStdString();
        string sTime = ui->startTime->text().toStdString();
        string eTime = ui->endTime->text().toStdString();
        string days = "";

        if (ui->monBox->isChecked())
            days += "1";
        else
            days += "0";
        if (ui->tuesBox->isChecked())
            days += "1";
        else
            days += "0";
        if (ui->wedBox->isChecked())
            days += "1";
        else
            days += "0";
        if (ui->thurBox->isChecked())
            days += "1";
        else
            days += "0";
        if (ui->friBox->isChecked())
            days += "1";
        else
            days += "0";

        string term = "0";

        if (ui->firHTermRadio->isChecked())
            term = "1";
        else if (ui->sndHTermRadio->isChecked())
            term = "2";

        int units = ui->unitsBox->value();
        course * o = new course(classNa,maj,sectN,fName,lName,sTime,eTime,days,term,units);

        int i = getit(dectime(sTime));
        int j = getit(dectime(eTime));
        while (i <= j) {
            o->puttaglist(i);
            ++i;
        }

        possibles.push_back(o);
        classes++;
        addToTable(o);
        clearAll();
    }
}

// Clears all the elements of the new course tab
void MainWindow::clearAll()
{
    ui->classNameBox->clear();
    ui->sectionBox->clear();
    ui->firstNameBox->clear();
    ui->lastNameBox->clear();
    ui->monBox->setChecked(false);
    ui->tuesBox->setChecked(false);
    ui->wedBox->setChecked(false);
    ui->thurBox->setChecked(false);
    ui->friBox->setChecked(false);
    ui->startTime->setTime(QTime(7,0));
    ui->endTime->setTime(QTime(8,0));
}

// Adds a course to the prospective course table
void MainWindow::addToTable(course *s)
{
    ui->sectTable->setSortingEnabled(false);
    ui->sectTable->setRowCount(classes);
    ui->sectTable->setItem(classes-1,0,new QTableWidgetItem(QString::fromStdString(s->getClassName())));
    ui->sectTable->setItem(classes-1,1,new QTableWidgetItem(QString::fromStdString(s->getMajor())));
    ui->sectTable->setItem(classes-1,2,new QTableWidgetItem(QString::fromStdString(s->getSectNum())));
    ui->sectTable->setItem(classes-1,3,new QTableWidgetItem(QString::fromStdString(s->getLastName() + ", " + s->getFirstName())));
    ui->sectTable->setItem(classes-1,4,new QTableWidgetItem(QString::fromStdString(s->getReadableDays() + " " + s->getStartTime() + "-" + s->getEndTime())));

    QString term;

    if (s->getTerm() == "1")
        term = "Half-Term(First half)";
    else if (s->getTerm() =="2")
        term = "Half-Term(Second half)";
    else
        term = "Full Term";

    ui->sectTable->setItem(classes-1,5,new QTableWidgetItem(term));
    ui->sectTable->setItem(classes-1,6,new QTableWidgetItem(QString::fromStdString(std::to_string(s->getUnits()))));


    ui->sectTable->setSortingEnabled(true);
}

// Displays all the sections in possible. Only used for testing purposes.
void MainWindow::displayAll()
{
    QMessageBox msg;

    for(int i = 0; i < classes; i++)
    {
        msg.setText(QString::fromStdString(possibles[i]->toString()));
        msg.exec();
    }
}

// Initializes a section object from a string.
void MainWindow::initobj(string s, course * o) {
    string put;
    int i = 0;
    int j;
    while (s.at(i) != '*') {
        put.push_back(s.at(i));
        ++i;
    }
    ++i;
    o->setSectNum(put);

    put.clear();
    while (s.at(i) != '*') {
        put.push_back(s.at(i));
        ++i;
    }
    ++i;
    o->setMajor(put);

    put.clear();
    while (s.at(i) != '*') {
        put.push_back(s.at(i));
        ++i;
    }
    ++i;
    o->setClassName(put);

    put.clear();
    while (s.at(i) != '*') {
        put.push_back(s.at(i));
        ++i;
    }
    ++i;
    o->setLastName(put
                   );
    put.clear();
    while (s.at(i) != '*') {
        put.push_back(s.at(i));
        ++i;
    }
    ++i;
    o->setFirstName(put);

    put.clear();
    while (s.at(i) != '*') {
        put.push_back(s.at(i));
        ++i;
    }
    ++i;
    o->setStartTime(put);

    put.clear();
    while (s.at(i) != '*') {
        put.push_back(s.at(i));
        ++i;
    }
    ++i;
    o->setEndTime(put);

    put.clear();
    while (s.at(i) != '*') {
        put.push_back(s.at(i));
        ++i;
    }
    ++i;
    o->setDays(put);

    put.clear();
    while (s.at(i) != '*') {
        put.push_back(s.at(i));
        ++i;
    }
    ++i;
    o->setTerm(put);

    put.clear();
    while (s.at(i) != '*') {
        put.push_back(s.at(i));
        ++i;
    }
    ++i;
    o->setUnits(std::stoi(put));

    i = getit(dectime(o->getStartTime()));
    j = getit(dectime(o->getEndTime()));
    while (i <= j) {
        o->puttaglist(i);
        ++i;
    }
}

// Compares two courses to see if any time conflicts occur
bool MainWindow::canadd(course * a, course *b) {
    string da = a->getDays();
    string db = b->getDays();
    vector<int> ta = a->gettaglist();
    vector<int> tb = b->gettaglist();
    if ((da == db) && (ta == tb))
        return false;
    for (unsigned int i = 0; i < da.size(); ++i) {
            if (da.at(i) == '1' && db.at(i) == '1') {
                for (unsigned int x = 0; x < ta.size(); ++x) {
                    for (unsigned int y = 0; y < tb.size(); ++y) {
                        if (ta.at(x) == tb.at(y))
                        {
                            QMessageBox msg;
                            msg.setText(QString::fromStdString("Time conflict: " + a->getReadableDays() + " " + a->getStartTime() + " - " + a->getEndTime() + " :: " + b->getReadableDays() + " " + b->getStartTime() + " - " + b->getEndTime()));
                            msg.exec();
                            return false;
                        }
                    }
                }
            }
        }
    return true;
}

// Adds a course to schedule and added vector.
void MainWindow::addcourse(course * o) {
    o->schedit();
    added.push_back(o);
    return;
}

/**
* MINCONV converts minutes to a decimal value for use in the
* double value that represents time converted to base 10
*/
double MainWindow::minconv(int x) {
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
double MainWindow::dectime(string s) {
    double result = 0.0;
    int min = 0;
    int i = 0;
    string substr;
    char c = s.at(i);
    if (s == "0:00")
        return 0.0;
    if (s.empty() || (!isdigit(s.at(0)))) {
        cout << "Invalid format\n";
        exit(EXIT_FAILURE);
    }
    while (c != ':') {
        substr += c;
        ++i;
        c = s.at(i);
    }
    result += stod (substr);
    substr.clear();
    ++i;
   // c = s.at(i);

    for(c = s.at(i); i < s.length() && isdigit(s.at(i)); i++)
    {
        substr += c;
    }

    /*
    while (isdigit(s.at(i)) && i < s.length()) {
        substr += c;
        ++i;
        c = s.at(i);
    }*/
    min = stoi (substr);
    result += minconv(min);
    return result;
}

/**
* GETIT will take the time double generated from DECTIME and
* use it to generate an iterator which will be used to populate
* the data structure for the schedule, allowing for detection
* of time conflicts.
*/
int MainWindow::getit(double x) {
    int result;
    double test = floor(x);
    result = static_cast<int>(test) * 2;
    if ((x - test) > 0.0)
        result += 1;
    return result;
}
