#include "fourniseur.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QFile>
#include <QTextStream>

Fourniseur::Fourniseur() {}

Fourniseur::  Fourniseur(const QString &id, const QString &nom, const QString &prenom,
                            int tel, const QString &email, const QDateTime &datetime)
   : identifiantf(id), nomf(nom), prenomf(prenom), telephonef(tel), emailf(email), datetimef(datetime) {}

bool Fourniseur::ajouter() {
    QSqlQuery query;
    query.prepare("INSERT INTO fournisseurs (identifiantf, nomf, prenomf, telephonef, emailf, datetimef) "
                  "VALUES (:id, :nom, :prenom, :tel, :email, :datetime)");
    query.bindValue(":id", identifiantf);
    query.bindValue(":nom", nomf);
    query.bindValue(":prenom", prenomf);
    query.bindValue(":tel", telephonef);
    query.bindValue(":email", emailf);
    query.bindValue(":datetime", datetimef);

    if (query.exec()) {
        return true;
    } else {
        qDebug() << "Erreur d'ajout de fournisseur:" << query.lastError().text();
        return false;
    }
}

QSqlQueryModel* Fourniseur::afficher() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM fourniseurs");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Téléphone"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date/Heure"));
    return model;
}

bool Fourniseur::supprimer(const QString &id) {
    QSqlQuery query;
    query.prepare("DELETE FROM fournisseurs WHERE identifiantf = :id");
    query.bindValue(":id", id);

    if (query.exec()) {
        return true;
    } else {
        qDebug() << "Erreur de suppression de fournisseur:" << query.lastError().text();
        return false;
    }
}

QSqlQueryModel* Fourniseur::rechercher(const QString &id) {
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM fournisseurs WHERE identifiantf LIKE :id");
    query.bindValue(":id", "%" + id + "%");
    query.exec();
    model->setQuery(query);
    return model;
}

QSqlQueryModel* Fourniseur::trierParDateTime() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM fournisseurs ORDER BY datetimef DESC");
    return model;
}
bool Fourniseur::modifier(const QString &id) {
    QSqlQuery query;
    query.prepare("UPDATE fournisseurs SET nom = :nom, prenom = :prenom, telephone = :telephone, email = :email, dateHeure = :dateHeure WHERE id = :id");
    query.bindValue(":nom", nomf);
    query.bindValue(":prenom", prenomf);
    query.bindValue(":telephone", telephonef);
    query.bindValue(":email", emailf);
    query.bindValue(":dateHeure", datetimef);
    query.bindValue(":id", id);

    return query.exec();
}
bool Fourniseur::enregistrerExcel(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Impossible d'ouvrir le fichier pour écriture:" << file.errorString();
        return false;
    }

    QTextStream out(&file);
    out << "Identifiant,Nom,Prénom,Téléphone,Email,Date/Heure\n";

    QSqlQuery query("SELECT * FROM fournisseurs");
    while (query.next()) {
        QString identifiant = query.value(0).toString();
        QString nom = query.value(1).toString();
        QString prenom = query.value(2).toString();
        QString telephone = query.value(3).toString();
        QString email = query.value(4).toString();
        QString datetime = query.value(5).toDateTime().toString("yyyy-MM-dd HH:mm:ss");

        out << identifiant << "," << nom << "," << prenom << ","
            << telephone << "," << email << "," << datetime << "\n";
    }

    file.close();
    return true;
}

