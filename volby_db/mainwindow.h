#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include "dialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    QSqlDatabase db;



public slots:
    void on_pushButton_clicked();


private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
