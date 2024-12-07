#include <QApplication>
#include "MainWindow.h"
#include "Connection.h"
#include "PreferencesDialog.h"
#include <QMessageBox>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Créer une instance de Connection pour établir la connexion à la base de données
    Connection c;
    bool test = c.createconnection();

    MainWindow w;  // Créer la fenêtre principale

    if (test) {


        // Ensuite, afficher la fenêtre principale
        w.show();

        // Afficher un message de succès de connexion à la base de données
        QMessageBox::information(nullptr, QObject::tr("Database is open"),
                                 QObject::tr("Connection successful.\nClick Cancel to exit."),
                                 QMessageBox::Cancel);
    } else {
        // Si la connexion échoue, afficher un message d'erreur
        QMessageBox::critical(nullptr, QObject::tr("Database is not open"),
                              QObject::tr("Connection is not successful.\nClick Cancel to exit."),
                              QMessageBox::Cancel);
    }

    return app.exec();
}
