#ifndef MAINWINDOW1_H
#define MAINWINDOW1_H
#include "mainwindow.h"
#include "mainwindow3.h"
#include "mainwindow2.h"


#include <QDialog>
QT_BEGIN_NAMESPACE
namespace Ui {
class mainwindow1;
}
QT_END_NAMESPACE

class mainwindow1 : public QDialog
{
    Q_OBJECT

public:
    explicit mainwindow1(QWidget *parent = nullptr);
    ~mainwindow1();
private slots:
    //void on_pushButton_5_clicked();

    //void on_pushButton_clicked();

    //void on_pushButton_2_clicked();

    //void on_pushButton_3_clicked();

    //void on_pushButton_6_clicked();*/
    void on_pushButton_2_clicked();



    void on_pushButton_3_clicked();

    void on_pushButton_clicked();


    void on_pushButtonB_clicked();

private:
    Ui::mainwindow1 *uii;
    Ui::MainWindow *ui;
    MainWindow *w;
    Ui::MainWindow3 *uui;
    MainWindow3 *l;
    Ui::MainWindow2 *uuii;
    MainWindow2 *m;


};

#endif // MAINWINDOW1_H


