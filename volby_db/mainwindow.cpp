#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../volby_db/db.sqlite");
    db.open();
    if(!db.open())
    {
        QMessageBox::warning(this,"nefunguje","RIP DB");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString name = ui->lineName->text();
    QString name2 = ui->lineName2->text();
    QString rodcis = ui->lineRodCis->text();

    int letterRod = 0;
    int numName = 0;
    int numName2 = 0;

    if(!name.isEmpty() && !name2.isEmpty() && !rodcis.isEmpty())
    {

         for(int i=0;i<=rodcis.length();++i)
        {
            if (!rodcis[i].isNumber())
            {
                letterRod++;
            }
        }
         for(int i=0;i<=name.length();++i)
        {
            if (!name[i].isLetter())
            {
                numName++;
            }
        }
          for(int i=0;i<=name2.length();++i)
        {
            if (!name2[i].isLetter())
            {
                numName2++;
            }
        }


        if(letterRod==1 || numName==1 || numName2 == 0)
        {
            QString rodCisControl = ui->lineRodCis->text();
            int rodCisCheck;
            QSqlQuery query;
            query.prepare("SELECT rodcis FROM volic WHERE rodcis = :rodcis");
            query.bindValue(":rodcis", rodCisControl);
            query.exec();

            while(query.next()){
                rodCisCheck = query.value(0).toInt();
             }
            if(rodCisCheck==NULL)
            {
                QSqlQuery dotaz;
                dotaz.prepare("INSERT INTO volic VALUES(:jmeno, :prijmeni, :rodcis)");
                dotaz.bindValue(":jmeno", name);
                dotaz.bindValue(":prijmeni", name2);
                dotaz.bindValue(":rodcis", rodcis);
                dotaz.exec();

                Dialog dialog(rodcis,this);
                dialog.exec();
            }
            else{
               QMessageBox::warning(this,"Pozor!","Vy už jste volil/a.","Ok","Cancel");
            }
        }
        else
        {
            QMessageBox::warning(this,"Pozor!","Špatný formát údajů.","Ok","Cancel");

        }
    }
    else
    {
        QMessageBox::warning(this,"Pozor!","zapomněl jste vyplnit všechny údaje.","Ok","Cancel");
    }


}
