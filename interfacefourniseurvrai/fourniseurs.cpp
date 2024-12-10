#include "fourniseurs.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QFile>
#include <QTextStream>

Fourniseur::Fourniseur() {}
Fourniseur:: Fourniseur(QString IDENTIFIANTF, QString NOMF, QString PRENOMF,int TELEPHONEF,QString EMAILF, QDateTime DATETIMEF )
{
    this->IDENTIFIANTF=IDENTIFIANTF;
    this->NOMF= NOMF;
    this->PRENOMF= PRENOMF;
    this->TELEPHONEF = TELEPHONEF;
    this->EMAILF = EMAILF;
    this->DATETIMEF = DATETIMEF;
};


bool Fourniseur::ajouter() {

    QSqlQuery query;
    query.prepare("INSERT INTO FOURNISEUR (IDENTIFIANTF, NOMF, PRENOMF, TELEPHONEF, EMAILF, DATETIMEF) "
                  "VALUES (:IDENTIFIANTF, :NOMF, :PRENOMF, :TELEPHONEF, :EMAILF, :DATETIMEF)");
    query.bindValue(":IDENTIFIANTF",IDENTIFIANTF);
    query.bindValue(":NOMF", NOMF);
    query.bindValue(":PRENOMF", PRENOMF);
    query.bindValue(":TELEPHONEF", TELEPHONEF);
    query.bindValue(":EMAILF", EMAILF);
    query.bindValue(":DATETIMEF", DATETIMEF);
qDebug() <<query.lastQuery();
qDebug() << "Valeur DATETIMEF lors de l'ajout:" << DATETIMEF.toString("yyyy-MM-dd HH:mm:ss");

    if (query.exec()) {
        return true;
    } else {
        qDebug() << "Erreur d'ajout de fournisseur:" << query.lastError().text();
        return false;
    }


}

QSqlQueryModel* Fourniseur::afficher() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM FOURNISEUR");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IDENTIFIANTF"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOMF"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOMF"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("TELEPHONEF"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAILF"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("DATETIMEF"));

        if (model->lastError().isValid()) {
            qDebug() << "Erreur d'affichage:" << model->lastError().text();
        }
    return model;

}

bool Fourniseur::supprimer(const QString &id) {
    QSqlQuery query;
    query.prepare("DELETE FROM FOURNISEUR WHERE identifiantf = :id");
    query.bindValue(":id", id);

    if (query.exec()) {
        qDebug() << "Fournisseur supprimé avec succès.";
        return true;
    } else {
        qDebug() << "Erreur de suppression de fournisseur:" << query.lastError().text();
        return false;
    }
}

QSqlQueryModel* Fourniseur::rechercher(const QString &id) {
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM FOURNISEUR WHERE identifiantf LIKE :id");
    query.bindValue(":id", "%" + id + "%");
    query.exec();
    model->setQuery(query);
    return model;
}

QSqlQueryModel* Fourniseur::trierParDateTime() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM FOURNISEUR ORDER BY datetimef DESC");

    if (model->lastError().isValid()) {
        qDebug() << "Erreur de tri par date/heure:" << model->lastError().text();
        delete model;
               return nullptr;
    } else {
        qDebug() << "Tri par date/heure réussi.";
    }

    return model;
}
bool Fourniseur::modifier(const QString &id, const QString &nom, const QString &prenom, int telephone, const QString &email) {
    QSqlQuery query;
    query.prepare("UPDATE FOURNISEUR SET NOMF = :nom, PRENOMF = :prenom, TELEPHONEF = :telephone, EMAILF = :email "
                  "WHERE IDENTIFIANTF = :identifiant");
    query.bindValue(":identifiant", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":telephone", telephone);
    query.bindValue(":email", email);

    // Ajoutez des messages de débogage pour vérifier les valeurs
    qDebug() << "Modification du fournisseur avec ID:" << id;
    qDebug() << "Nom:" << nom << "Prénom:" << prenom << "Téléphone:" << telephone << "Email:" << email;
    qDebug() << "Requête SQL:" << query.lastQuery();

    if (query.exec()) {
        qDebug() << "Fournisseur modifié avec succès.";
        return true;
    } else {
        qDebug() << "Échec de la modification du fournisseur:" << query.lastError().text();
        return false;
    }

}
bool Fourniseur::enregistrerExcel(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Impossible d'ouvrir le fichier pour écriture:" << file.errorString();
        return false;
    }

    QTextStream out(&file);
    out << "Identifiant,Nom,Prénom,Téléphone,Email,Date/Heure\n";

    QSqlQuery query("SELECT * FROM FOURNISEUR");
    while (query.next()) {
        QString IDENTIFIANTF = query.value(0).toString();
        QString NOMF = query.value(1).toString();
        QString PRENOMF= query.value(2).toString();
        QString TELEPHONEF= query.value(3).toString();
        QString EMAILF = query.value(4).toString();
        QString DATETIMEF = query.value(5).toDateTime().toString("yyyy-MM-dd HH:mm:ss");

        out << IDENTIFIANTF << "," << NOMF<< "," <<PRENOMF<< ","
            << TELEPHONEF << "," << EMAILF << "," << DATETIMEF << "\n";
    }

    file.close();
    return true;
}
