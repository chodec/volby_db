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


private slots:
    void on_export_2_clicked();

    void on_import_2_clicked();

private:
    Ui::MainWindow *ui;
    void save(const QString &filename);
    void load(const QString &filename);
};

#endif // MAINWINDOW_H
