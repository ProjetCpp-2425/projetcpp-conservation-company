#include "mainwindow.h"
#include "connexion.h"
#include <QApplication>
#include <QMessageBox>
#include<QString>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    // Création de l'objet connexion
    Connection c;
    bool test = c.createconnection(); // Tente d'établir la connexion

    if (test) {
        // Si la connexion est réussie, afficher la fenêtre principale
        w.show();
        QMessageBox::information(nullptr, QObject::tr("Database Connection"),
                                 QObject::tr("Connection successful.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    } else {
        // Si la connexion échoue, afficher un message d'erreur
        QMessageBox::critical(nullptr, QObject::tr("Database Connection"),
                              QObject::tr("Connection failed.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }

    return a.exec(); // Boucle principale de l'application
}
