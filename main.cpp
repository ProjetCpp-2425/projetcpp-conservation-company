#include <QApplication>
#include <QDebug>
#include "connexion.h"
#include "fourniseur.h"
#include"mainwindow.h"
#include <QSqlQuery>
#include <QSqlRecord>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Connection c;
    bool test=c.createconnection();
    MainWindow w;
    if (!c.createconnection()) {
        qDebug() << "Échec de la connexion à la base de données.";
        return -1;
    }
    qDebug() << "Connexion à la base de données réussie.";


    Fourniseur fourniseur("F001", "Dupont", "Marie", QString("0123456789").toInt(), "marie.dupont@example.com", QDateTime::currentDateTime());

    if (fourniseur.ajouter()) {
        qDebug() << "Fournisseur ajouté avec succès.";
    } else {
        qDebug() << "Erreur lors de l'ajout du fournisseur.";
    }


    QSqlQueryModel *model = fourniseur.afficher();
    for (int i = 0; i < model->rowCount(); ++i) {
        QString identifiant = model->record(i).value("identifiantf").toString();
        QString nom = model->record(i).value("nomf").toString();
        QString prenom = model->record(i).value("prenomf").toString();
        qDebug() << "Identifiant:" << identifiant << ", Nom:" << nom << ", Prénom:" << prenom;
    }

    if (fourniseur.supprimer("F001")) {
        qDebug() << "Fournisseur supprimé avec succès.";
    } else {
        qDebug() << "Erreur lors de la suppression du fournisseur.";
    }


    QSqlQueryModel *sortedModel = fourniseur.trierParDateTime();
    qDebug() << "Fournisseurs triés par date/heure:";
    for (int i = 0; i < sortedModel->rowCount(); ++i) {
        QString identifiant = sortedModel->record(i).value("identifiantf").toString();
        QString nom = sortedModel->record(i).value("nomf").toString();
        QString prenom = sortedModel->record(i).value("prenomf").toString();
        QString datetime = sortedModel->record(i).value("datetimef").toDateTime().toString("yyyy-MM-dd HH:mm:ss");
        qDebug() << "Identifiant:" << identifiant << ", Nom:" << nom << ", Prénom:" << prenom << ", Date/Heure:" << datetime;
    }


    QString filePath = "fourniseurs.csv";
    if (fourniseur.enregistrerExcel(filePath)) {
        qDebug() << "Données des fournisseurs enregistrées dans le fichier" << filePath;
    } else {
        qDebug() << "Erreur lors de l'enregistrement des données dans le fichier Excel.";
    }


    c.closeConnection();

    return a.exec();
}
