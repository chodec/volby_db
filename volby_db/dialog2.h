#ifndef DIALOG2_H
#define DIALOG2_H

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsSimpleTextItem>
#include "dialog.h"


namespace Ui {
class Dialog2;
}

class Dialog2 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog2(QWidget *parent = 0);
    ~Dialog2();

private:
    Ui::Dialog2 *ui;
     QGraphicsScene *scene;

     QGraphicsSimpleTextItem *ods;
     QGraphicsSimpleTextItem *ano;
     QGraphicsSimpleTextItem *pirati;
};

#endif // DIALOG2_H
