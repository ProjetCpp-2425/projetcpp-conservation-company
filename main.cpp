#include "mainwindow.h"
#include "connection.h"
#include <QMessageBox>
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection c;
    bool test = c.createconnection();
    MainWindow w;
    if (test)
    {
        w.show();
        QMessageBox::information(nullptr, QObject::tr("Database is open"), QObject::tr("Connection successful.\nClick Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Database is not open"), QObject::tr("Connection is not successful.\nClick Cancel to exit."), QMessageBox::Cancel);
    }
    return a.exec();
}
