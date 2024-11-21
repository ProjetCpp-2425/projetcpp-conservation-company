// produit.cpp
#include "produit.h"

Produit::Produit(QString nom, QString code_barres, QString type, int quantite, QString date_produit)
    : nom(nom), code_barres(code_barres), type(type), quantite(quantite), date_produit(date_produit)
{
}

bool Produit::ajouter() {
    QSqlQuery query;
    query.prepare("INSERT INTO produits (nom, code_barres, type, quantite, date_produit) "
                  "VALUES (:nom, :code_barres, :type, :quantite, TO_DATE(:date_produit, 'YYYY-MM-DD'))");

    query.bindValue(":nom", nom);
    query.bindValue(":code_barres", code_barres);
    query.bindValue(":type", type);
    query.bindValue(":quantite", quantite);
    query.bindValue(":date_produit", date_produit);

    if (query.exec()) {
        return true;
    } else {
        qDebug() << "Error adding product:" << query.lastError().text()
                 << "\nValues:"
                 << "\nnom:" << nom
                 << "\ncode_barres:" << code_barres
                 << "\ntype:" << type
                 << "\nquantite:" << quantite
                 << "\ndate_produit:" << date_produit;
        return false;
    }
}

bool Produit::supprimer(QString code_barres) {
    QSqlQuery query;
    query.prepare("DELETE FROM produits WHERE code_barres = :code_barres");
    query.bindValue(":code_barres", code_barres);
    return query.exec();
}

QSqlQueryModel* Produit::afficher() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT nom, code_barres, type, quantite, date_produit FROM produits ORDER BY nom");
    return model;
}


