#include "connexion.h"

Connection::Connection()
{

}

bool Connection::createconnection()
{if (QSqlDatabase::contains("qt_sql_default_connexion"))
    {
        qDebug()<<"connexion a la base de donnes deja etablir.";
        return true;
    }
    bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC","qt_sql_default_connection");
db.setDatabaseName("source2a32");//inserer le nom de la source de données
db.setUserName("projetcpp2a32");//inserer nom de l'utilisateur
db.setPassword("mp2a32");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;
return  test;
}
void Connection::closeConnection(){db.close();}
