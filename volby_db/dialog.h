#ifndef DIALOG_H
#define DIALOG_H
#include "mainwindow.h"
#include <QDialog>
#include "dialog2.h"


namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QString rodcis,QWidget *parent = 0);
     ~Dialog();



private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::Dialog *ui;
    QString RodCis;

};

#endif // DIALOG_H
