#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>
#include <QDate>
#include <QStringList>
#include <QSqlQuery>
#include <QMessageBox>


Dialog::Dialog(QString rodcis, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->RodCis = rodcis;
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_buttonBox_accepted()
{
    QString strana = ui->comboBox->currentText();
    QDate date = QDate::currentDate();
    QString rokStr = date.toString("yyyy-MM-dd");
    QString rok = rokStr.mid(0, rokStr.indexOf("-"));

    QSqlQuery dotaz;
    dotaz.prepare("INSERT INTO hlasy VALUES(:rodcis, :strana, :rok)");
    dotaz.bindValue(":rodcis", RodCis);
    dotaz.bindValue(":strana", strana);
    dotaz.bindValue(":rok", rok);
    dotaz.exec();
          Dialog2 dialog2;
   switch(QMessageBox::question(this,"Ještě neodcházejte!",
                                "Chcete vidět graf průběhu voleb?"))
   {
      case QMessageBox::Yes:

          dialog2.exec();
        qDebug() << "yes";
           break;
       case QMessageBox::No:
        qDebug() << "no";
           break;
       case QMessageBox::Escape:
           qDebug() << "esc";
           break;
           default:
               qDebug()<< "vychozi";
           }

}

void Dialog::on_buttonBox_rejected()
{
    QString sql = "DELETE FROM volic WHERE rodcis="+RodCis;
    QSqlQuery dotaz;
    dotaz.prepare(sql);
    dotaz.exec();


}
