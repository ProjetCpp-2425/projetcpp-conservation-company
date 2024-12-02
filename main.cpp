#include "mainwindow.h"
#include "connection.h"
#include <QApplication>
#include <QMessageBox>
#include <QSerialPort>
#include <QSerialPortInfo>
#include "arduino.h"  // Inclure le fichier d'en-tête de la classe Arduino

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    connection c;

    // Tentative de connexion à la base de données
    bool test = c.createconnect();

    // Créer une instance de la classe Arduino
    Arduino arduino;

    // Essayer de se connecter au port série
    if (arduino.openConnection("COM4")) {  // Remplacez "COMx" par le port série correct (par exemple, "COM3")
        qDebug() << "Connexion série réussie!";
    } else {
        qDebug() << "Échec de la connexion série!";
    }

    // Vérifier si la connexion à la base de données est réussie
    if (test) {
        w.show();
        QMessageBox::information(nullptr, QObject::tr("Database is open"),
                    QObject::tr("Connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Database is not open"),
                    QObject::tr("Connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

    // Connecter le signal de réception de données de l'Arduino à un slot pour traiter les données reçues
    //QObject::connect(&arduino, &Arduino::dataReceived, [&w](const QByteArray &data) {
        //qDebug() << "Données reçues de l'Arduino:" << data;
        // Vous pouvez ajouter ici la logique pour manipuler ces données dans votre interface Qt
        // Par exemple, mettre à jour un champ dans l'interface graphique avec les données reçues
   // });

    return a.exec();
}
