#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFileDialog>

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


        if(letterRod==1 && numName==1 && numName2 == 1)
        {
            QString rodCisControl = ui->lineRodCis->text();
            int rodCisCheck = 0;
            QSqlQuery query;
            query.prepare("SELECT rodcis FROM volic WHERE rodcis = :rodcis");
            query.bindValue(":rodcis", rodCisControl);
            query.exec();

            while(query.next()){
                rodCisCheck = query.value(0).toInt();
             }
            if(rodCisCheck==1)
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
void MainWindow::save(const QString &filename)
{
    QFile soubor(filename);
    if(!soubor.open(QIODevice::WriteOnly))
    {
        qWarning() << "vypadni! " << filename;
        return;
    }
    QJsonDocument export_doc;
    QJsonObject export_obj;
    QJsonArray volic;
    QSqlQuery dotaz;
    dotaz.prepare("SELECT * FROM volic");
    dotaz.exec();
    while(dotaz.next())
    {
        volic["jmeno"] = dotaz.value("jmeno").toString();
        volic["prijmeni"] = dotaz.value("prijmeni").toString();
        volic["rodcis"] = dotaz.value("rodcis").toInt();
        QJsonArray hlasy;
        QSqlQuery dotaz_hlasy;
        dotaz_hlasy.prepare("SELECT * FROM hlasy WHERE rodcis = :rodcis");
        dotaz_hlasy.bindValue(":rodcis", dotaz.value("rodcis").toInt());
        dotaz_hlasy.exec();
        while(dotaz_hlasy.next())
        {
            hlasy.append(dotaz_hlasy.value("strana").toString());
        }
        volic["hlasy"] = hlasy;
    }
    export_obj["volic"] = volic;
    export_doc.setObject(export_obj);
    soubor.write(export_doc.toJson());
    soubor.close();
}

void MainWindow::load(const QString &filename)
{
    QFile f(filename);
    if(!f.open(QIODevice::ReadOnly))
    {
        qWarning() << "zase rip " << filename;
        return;
    }
    QJsonDocument doc = QJsonDocument::fromJson(f.readAll());
    QJsonObject object_doc = doc.object();
    QJsonArray hlasy = object_doc["hlasy"].toArray();
    for(int i=0; i<hlasy.count(); ++i)
    {
        QSqlQuery dotaz;
        dotaz.prepare("INSERT INTO hlasy VALUES (:rodcis, :strana)");
        dotaz.bindValue(":rodcis", hlasy[i].toObject()["rocis"].toInt());
        dotaz.bindValue(":strana", hlasy[i].toObject()["strana"].toString());
        dotaz.exec();

    }
    QJsonArray volic = object_doc["volic"].toArray();
    for(int i=0; i<volic.count(); ++i)
    {
        QSqlQuery dotaz;
        dotaz.prepare("INSERT INTO volic VALUES (:jmeno, :prijmeni, :vek)");
        dotaz.bindValue(":jmeno", volic[i].toObject()["jmeno"].toString());
        dotaz.bindValue(":prijmeni", volic[i].toObject()["prijmeni"].toString());
        dotaz.bindValue(":rodcis", volic[i].toObject()["rodcis"].toInt());
        dotaz.exec();
        int volic_id = dotaz.lastInsertId().toInt();
       QJsonArray hlasy = volic[i].toObject()["hlasy"].toArray();
        for(int j=0; j<hlasy.count();++j)
        {
            dotaz.prepare("INSERT INTO hlasy VALUES (:rodcis, :strana)");
            dotaz.bindValue(":rodcis", volic_id);
            dotaz.bindValue(":strana", hlasy[j].toString());
            dotaz.exec();
        }

}

void MainWindow::on_export_2_clicked()
{
    QString path =QFileDialog::getSaveFileName(this, "Kam chceš exportovat?");
    if(path!= "")
        save(path);
}

void MainWindow::on_import_2_clicked()
{
    QString path =QFileDialog::getOpenFileName(this, "Kam chceš exportovat?");
    if(path!= "")
        load(path);
}
