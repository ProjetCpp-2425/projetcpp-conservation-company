
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include "connection.h"
Connection::Connection()
{
    // Initialisation de l'objet QSqlDatabase si nécessaire
}

bool Connection::createconnection()
{
    // Connexion à la base de données
    db = QSqlDatabase::addDatabase("QODBC"); // Remplacez "QOCI" par le driver SQL approprié (par exemple "QMYSQL" pour MySQL, "QPSQL" pour PostgreSQL)
    db.setDatabaseName("CPP_project"); // Remplacez par le nom de votre base de données
    db.setUserName("projetcpp2a32"); // Remplacez par votre nom d'utilisateur
    db.setPassword("mp2a32"); // Remplacez par votre mot de passe

    if (!db.open()) {
        qDebug() << "Erreur lors de la connexion à la base de données:" << db.lastError().text();
        return false;
    }

    qDebug() << "Connexion à la base de données réussie!";
    return true;
}

void Connection::closeConnection()
{
    db.close();
    qDebug() << "Connexion à la base de données fermée!";
}
