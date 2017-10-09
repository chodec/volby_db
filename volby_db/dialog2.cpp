#include "dialog2.h"
#include "ui_dialog2.h"

#include <QSqlQuery>
#include <QDebug>

Dialog2::Dialog2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog2)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);

    ods = new QGraphicsSimpleTextItem("ODS");
    ano = new QGraphicsSimpleTextItem("ANO");
    pirati = new QGraphicsSimpleTextItem("Piráti");

    ods->setPos(-105,520);
    ano->setPos(-20,520);
    pirati->setPos(60,520);

    ui->graphicsView->setScene(scene);

    QString sAno = "ANO";
    QString sPirati = "Piráti";
    QString sOds = "ODS";

    int anoCount;
    int odsCount;
    int piratiCount;

    QSqlQuery dotaz;
    dotaz.prepare("SELECT COUNT(strana) FROM hlasy WHERE strana = :strana");
    dotaz.bindValue(":strana",sAno);
    dotaz.exec();
    if(dotaz.next()){
        anoCount = dotaz.value(0).toInt();
    }
    QSqlQuery dotaz2;
    dotaz2.prepare("SELECT COUNT(strana) FROM hlasy WHERE strana = :strana");
    dotaz2.bindValue(":strana",sPirati);
    dotaz2.exec();
    if(dotaz2.next()){
        piratiCount = dotaz2.value(0).toInt();
    }
    QSqlQuery dotaz3;
    dotaz3.prepare("SELECT COUNT(strana) FROM hlasy WHERE strana = :strana");
    dotaz3.bindValue(":strana", sOds);
    dotaz3.exec();
    if(dotaz3.next()){
        odsCount = dotaz3.value(0).toInt();
    }
    scene->addLine(-170,500,170,500,QPen(Qt::black));
    scene->addLine(-140,520,-140,300,QPen(Qt::black));
    scene->addRect(-135,499,80, -odsCount*3,QPen(Qt::black),QBrush(Qt::yellow));
    scene->addRect(-50,499,80,-anoCount*3,QPen(Qt::black),QBrush(Qt::blue));
    scene->addRect(35,499,80,-piratiCount*3,QPen(Qt::black),QBrush(Qt::green));
    scene->addItem(ods);
    scene->addItem(ano);
    scene->addItem(pirati);
}

Dialog2::~Dialog2()
{
    delete ui;
}
