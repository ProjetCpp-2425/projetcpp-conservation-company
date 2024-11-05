#include "client.h"
#include <QSqlQuery>
#include <QtDebug>
#include<QSqlError>
#include<QObject>
#include<QMessageBox>//afficher un message de succès ou d'échec d'une opération
#include<map>
#include <QSqlQueryModel>

client::client()
{
IDENTIFIANT=""; NOM=""; PRENOM=""; TELEPHONE=0; EMAIL="";
}


client::client(QString IDENTIFIANT,QString NOM,QString PRENOM,QString EMAIL, int TELEPHONE )
{this->IDENTIFIANT=IDENTIFIANT; this->NOM=NOM; this->PRENOM=PRENOM;this->TELEPHONE=TELEPHONE;this->EMAIL=EMAIL;}

int client:: getTELEPHONE(){return TELEPHONE;}
QString client:: getNOM(){return NOM;}
QString client::getPRENOM(){return PRENOM;}
QString client::getEMAIL(){return EMAIL;}
QString client::getIDENTIFIANT(){return IDENTIFIANT;}
void client::setTELEPHONE(int TELEPHONE){this->TELEPHONE=TELEPHONE;}
void client::setNOM(QString NOM){this->NOM=NOM;}
void client::setPRENOM(QString PRENOM){this->PRENOM=PRENOM;}
void client::setEMAIL(QString EMAIL){this->EMAIL=EMAIL;}
void client::setIDENTIFIANT(QString IDENTIFIANT){this->IDENTIFIANT=IDENTIFIANT;}


bool client::ajouter()
{
    QSqlQuery query;

    query.prepare("INSERT INTO CLIENT (IDENTIFIANT, NOM, PRENOM, EMAIL, TELEPHONE) "
                  "VALUES (:IDENTIFIANT, :NOM, :PRENOM, :EMAIL, :TELEPHONE)");

    query.bindValue(":IDENTIFIANT", IDENTIFIANT);// permet d'ajouter dans le champs préparer par prepare
    query.bindValue(":NOM", NOM);
    query.bindValue(":PRENOM", PRENOM);
    query.bindValue(":EMAIL", EMAIL); // Assurez-vous que TÉLÉPHONE est un entier
    query.bindValue(":TELEPHONE", TELEPHONE);

    qDebug() << query.lastQuery(); // Afficher la requête préparée pour le débogage

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'insertion : " << query.lastError().text();
        return false; // Échec de l'insertion
    }

    return true; // Insertion réussie
}




QSqlQueryModel* client::afficher() {
    QSqlQueryModel* model = new QSqlQueryModel();

    // Définir la requête SQL pour obtenir les données de la table CLIENT
    model->setQuery("SELECT * FROM CLIENT");

    // Définir les en-têtes de colonnes pour l'affichage
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IDENTIFIANT"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("TELEPHONE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL"));

    return model;
}







        bool client::supprimer(QString IDENTIFIANT) {
            IDENTIFIANT = IDENTIFIANT.trimmed();  // Supprimer les espaces et caractères non imprimables

            if (!QSqlDatabase::database().isOpen()) {
                qDebug() << "La base de données n'est pas ouverte. Vérifiez la connexion.";
                return false;
            }

            QSqlQuery query;

            // Vérifiez si l'identifiant existe
            query.prepare("SELECT COUNT(*) FROM CLIENT WHERE IDENTIFIANT = :IDENTIFIANT");
            query.bindValue(":IDENTIFIANT", IDENTIFIANT);

            if (!query.exec()) {
                qDebug() << "Erreur lors de la vérification de l'existence de l'identifiant : " << query.lastError().text();
                return false;
            }

            query.next();//va récupérer le nombre de clients correspondant à l'identifiant.
            int count = query.value(0).toInt();
            qDebug() << "Count for IDENTIFIANT" << IDENTIFIANT << ":" << count;

            if (count == 0) {
                qDebug() << "Identifiant non trouvé : " << IDENTIFIANT;
                return false;
            }

            // Si l'identifiant existe, procédez à la suppression
            query.prepare("DELETE FROM CLIENT WHERE IDENTIFIANT = :IDENTIFIANT");
            query.bindValue(":IDENTIFIANT", IDENTIFIANT);

            if (!query.exec()) {
                qDebug() << "Erreur lors de la suppression : " << query.lastError().text();
                return false;
            }

            return true;
        }


        bool client::Modifier(QString IDENTIFIANT, QString NOM, QString PRENOM,QString EMAIL, int TELEPHONE)
        {
            QSqlQuery query;
            QString TELEPHONE_string =QString::number(TELEPHONE);
            query.prepare("UPDATE Client SET NOM=:NOM ,PRENOM=:PRENOM, EMAIL=:EMAIL, TELEPHONE=:TELEPHONE WHERE IDENTIFIANT=:IDENTIFIANT");

            query.bindValue(":IDENTIFIANT",IDENTIFIANT);
            query.bindValue(":NOM", NOM);
            query.bindValue(":PRENOM", PRENOM);
            query.bindValue(":EMAIL", EMAIL);
            query.bindValue(":TELEPHONE",TELEPHONE_string);

             return  query.exec();

     }








