#ifndef PRODUIT_H
#define PRODUIT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlError>
#include <QDate>
#include <QDebug>
#include <QSqlQueryModel>

class Produit
{
public:
    // Constructeurs
    Produit(); // Constructeur par défaut
    Produit(const QString& nom, const QString& code_barres, const QString& type,
            int quantite, const QString& date_produit);

    // Méthodes publiques
    bool ajouter();                      // Ajouter un nouveau produit à la base de données
    static bool supprimer(const QString& code_barres); // Supprimer un produit via son code-barres
    static QSqlQueryModel* afficher();  // Afficher tous les produits

    // Accesseurs (getters) pour lire les membres privés
    QString getNom() const;
    QString getCodeBarres() const;
    QString getType() const;
    int getQuantite() const;
    QString getDateProduit() const;

    // Mutateurs (setters) pour modifier les membres privés
    void setNom(const QString& nom);
    void setCodeBarres(const QString& code_barres);
    void setType(const QString& type);
    void setQuantite(int quantite);
    void setDateProduit(const QString& date_produit);
    // Membres privés
    QString m_nom;               // Nom du produit
    QString m_code_barres;       // Code-barres
    QString m_type;              // Type ou catégorie
    int m_quantite;              // Quantité
    QString m_date_produit;      // Date du produit (au format chaîne)
    QDate m_date_associate;

};
#endif // PRODUIT_H
