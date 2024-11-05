#ifndef FOURNISEUR_H
#define FOURNISEUR_H

#include <QString>
#include <QDateTime>
#include <QSqlQueryModel>

class Fourniseur {
public:
    // Constructeur par défaut
    Fourniseur();

    // Constructeur avec paramètres
    Fourniseur(const QString &id, const QString &nom, const QString &prenom,
                int tel, const QString &email, const QDateTime &datetime);

    // Méthodes
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(const QString &id);
    QSqlQueryModel* rechercher(const QString &id);
    QSqlQueryModel* trierParDateTime();
    bool enregistrerExcel(const QString &filePath);
bool modifier(const QString &id);
private:
    QString identifiantf;
    QString nomf;
    QString prenomf;
    int telephonef;  // Numéro de téléphone de type int
    QString emailf;
    QDateTime datetimef;
};

#endif // FOURNISEUR_H
