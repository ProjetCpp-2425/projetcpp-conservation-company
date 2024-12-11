#include "mainwindow1.h"
#include "ui_mainwindow1.h"
#include<QLabel>
#include<QPixmap>


mainwindow1::mainwindow1(QWidget *parent) :
    QDialog(parent),
    uii(new Ui::mainwindow1)
{
    uii->setupUi(this);
    QPixmap pixmap("C:/Users/Tayma Store/Desktop/integration/logo.png");

        if (!pixmap.isNull()) {
            uii->labelLogo->setPixmap(pixmap); // Affecter l'image au QLabel
            uii->labelLogo->setScaledContents(true); // L'image s'adapte à la taille du QLabel
        } else {
            qDebug() << "Erreur : Impossible de charger l'image.";
        }

}

mainwindow1::~mainwindow1()
{
    delete uii;
}




/*void mainwindow1::on_pushButton_2_clicked()
{

        n=new MainWindow3(this);
                n->show();

}

void mainwindow2::on_pushButton_3_clicked()
{
    l=new MainWindow4(this);
            l->show();

}

void mainwindow2::on_pushButton_6_clicked()
{
    z=new gestion_salle(this);
            z->show();
}

void mainwindow2::on_pushButton_5_clicked()
{
    s=new GestionReservation(this);
            s->show();
}
*/


void mainwindow1::on_pushButton_2_clicked()
{
    w=new MainWindow(this);
            w->show();


}


void mainwindow1::on_pushButton_3_clicked()
{
    l=new MainWindow3(this);
            l->show();

}


void mainwindow1::on_pushButton_clicked()
{
    m=new MainWindow2(this);
            m->show();

}









void mainwindow1::on_pushButtonB_clicked()
{

}

