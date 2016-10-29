#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <section.h>
#include <QVector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_schedButt_clicked();
    void save();
    void load();
    void displayAll();

private:
    Ui::MainWindow *ui;
    void clearAll();
    void addToTable(course*);
    void initobj(string s, course * o);
    bool canadd(course * a, course * b);
    double minconv(int x);
    double dectime(string s);
    int getit(double x);
    void addcourse(course *);
    void dispSched();
    QVector<course *> added;
    QVector<course *> possibles;
    int classes;
    void clearSched();
};

#endif // MAINWINDOW_H
