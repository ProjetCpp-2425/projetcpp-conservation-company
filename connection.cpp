// connection.cpp
#include "connection.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

Connection::Connection()
{
    // L'initialisation sera faite dans createconnection()
}

bool Connection::createconnection()
{
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("CPP_project");
    db.setUserName("projetcpp2a32");
    db.setPassword("mp2a32");

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
