#include "produit.h"

Produit::Produit()
    : m_nom(""), m_code_barres(""), m_type(""), m_quantite(0), m_date_produit(""), m_date_associate(QDate::currentDate()) {}

Produit::Produit(const QString& nom, const QString& code_barres, const QString& type,
                 int quantite, const QString& date_produit)
    : m_nom(nom), m_code_barres(code_barres), m_type(type), m_quantite(quantite), m_date_produit(date_produit)
{
    // Conversion de la chaîne date_produit en QDate si nécessaire
    m_date_associate = QDate::fromString(date_produit, "yyyy-MM-dd");
}

bool Produit::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO produits (nom, code_barres, type, quantite, date_produit) "
                  "VALUES (:nom, :code_barres, :type, :quantite, TO_DATE(:date_produit, 'YYYY-MM-DD'))");

    query.bindValue(":nom", m_nom);
    query.bindValue(":code_barres", m_code_barres);
    query.bindValue(":type", m_type);
    query.bindValue(":quantite", m_quantite);
    query.bindValue(":date_produit", m_date_produit);

    // Exécution de la requête
    if (!query.exec()) {
        qDebug() << "Erreur lors de l'ajout du produit : " << query.lastError().text();
        qDebug() << "Détails de la requête SQL : " << query.lastQuery();
        return false;
    }

    return true;
}


bool Produit::supprimer(const QString& code_barres) {
    QSqlQuery query;
    query.prepare("DELETE FROM produits WHERE code_barres = :code_barres");
    query.bindValue(":code_barres", code_barres);

    if (query.exec()) {
        return true;
    } else {
        qDebug() << "Erreur lors de la suppression du produit:" << query.lastError().text();
        return false;
    }
}

QSqlQueryModel* Produit::afficher() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT nom, code_barres, type, quantite, date_produit FROM produits ORDER BY nom");

    if (model->lastError().isValid()) {
        qDebug() << "Erreur lors de l'affichage des produits:" << model->lastError().text();
        delete model;  // Nettoyage en cas d'erreur
        return nullptr;
    }

    return model;
}

// Getters
QString Produit::getNom() const { return m_nom; }
QString Produit::getCodeBarres() const { return m_code_barres; }
QString Produit::getType() const { return m_type; }
int Produit::getQuantite() const { return m_quantite; }
QString Produit::getDateProduit() const { return m_date_produit; }

// Setters
void Produit::setNom(const QString& nom) { m_nom = nom; }
void Produit::setCodeBarres(const QString& code_barres) { m_code_barres = code_barres; }
void Produit::setType(const QString& type) { m_type = type; }
void Produit::setQuantite(int quantite) { m_quantite = quantite; }
void Produit::setDateProduit(const QString& date_produit) {
    m_date_produit = date_produit;
    m_date_associate = QDate::fromString(date_produit, "yyyy-MM-dd");
}
