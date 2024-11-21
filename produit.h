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
    // Constructor
    Produit(QString nom, QString code_barres, QString type, int quantite, QString date_produit);

    // Member functions
    bool ajouter();                     // Add a new product
    static bool supprimer(QString code_barres); // Delete a product by its barcode
    static QSqlQueryModel* afficher(); // Fetch and display products (optional if unused)

private:
    // Member variables
    QString nom;                        // Product name
    QString code_barres;                // Barcode
    QString type;                       // Type or category of product
    int quantite;                       // Quantity of the product
    QString date_produit;               // Date the product was added
    QDate associated;                   // Date associated with the product
};

#endif // PRODUIT_H
