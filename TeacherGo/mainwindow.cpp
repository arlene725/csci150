#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "section.h"
#include <QMessageBox>
#include <QTime>
#include <QString>
#include <string>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>
#include <QVector>

using std::string;

QVector<section*> sects(20);
int count;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    count = 0;
    ui->setupUi(this);
    //connect(ui->pushButton, SIGNAL(pressed()), this, SLOT(on_pushButton_clicked()));
    connect(ui->actionSave, SIGNAL(triggered(bool)), this, SLOT(save()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::save()
{
        QFile file(QFileDialog::getSaveFileName(this, tr("Save courses"), QDir::currentPath(), tr("Data (*dat)")));

        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
                return;
        QTextStream out(&file);
        for(int i = 0;i < count;i++)
        {
            out << QString::fromStdString(sects[i]->toString()) << "\n";
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
            days += "M";
        if (ui->tuesBox->isChecked())
            days += "Tu";
        if (ui->wedBox->isChecked())
            days += "W";
        if (ui->thurBox->isChecked())
            days += "Th";
        if (ui->friBox->isChecked())
            days += "F";

        int term = 0;

        if (ui->firHTermRadio->isChecked())
            term = 1;
        else if (ui->sndHTermRadio->isChecked())
            term = 2;

        sects[count++] = new section(classNa,maj,sectN,fName,lName,sTime,eTime,days,term);
        addToTable(sects[count-1]);
        clearAll();
    }
}

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

void MainWindow::addToTable(section *s)
{
    ui->sectTable->setSortingEnabled(false);
    ui->sectTable->setRowCount(count);
    ui->sectTable->setItem(count-1,0,new QTableWidgetItem(QString::fromStdString(s->getClassName())));
    ui->sectTable->setItem(count-1,1,new QTableWidgetItem(QString::fromStdString(s->getMajor())));
    ui->sectTable->setItem(count-1,2,new QTableWidgetItem(QString::fromStdString(s->getSectNum())));
    ui->sectTable->setItem(count-1,3,new QTableWidgetItem(QString::fromStdString(s->getLastName() + ", " + s->getFirstName())));
    ui->sectTable->setItem(count-1,4,new QTableWidgetItem(QString::fromStdString(s->getDays() + " " + s->getStartTime() + "-" + s->getEndTime())));

    QString term;
    int t = s->getTerm();

    if (s->getTerm() == 1)
        term = "Half-Term(First half)";
    else if (s->getTerm())
        term = "Half-Term(Second half)";
    else
        term = "Full Term";

    ui->sectTable->setItem(count-1,5,new QTableWidgetItem(term));


    ui->sectTable->setSortingEnabled(true);
}

void MainWindow::displayAll()
{
    QMessageBox msg;

    for(int i = 0; i < count; i++)
    {
        msg.setText(QString::fromStdString(sects[i]->toString()));
        msg.exec();
    }
}
