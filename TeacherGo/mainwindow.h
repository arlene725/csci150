#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <section.h>

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
    void save();
    void displayAll();

private:
    Ui::MainWindow *ui;
    void clearAll();
    void addToTable(section*);
};

#endif // MAINWINDOW_H
