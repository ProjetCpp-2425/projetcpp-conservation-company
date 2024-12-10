#ifndef FOURNISEUR_H
#define FOURNISEUR_H

#include <QString>
#include <QDateTime>
#include <QSqlQueryModel>
#include <QTableView>
class Fourniseur {
public:
    // Constructeur par défaut
    Fourniseur();

    // Constructeur avec paramètres
   Fourniseur(QString IDENTIFIANTF, QString NOMF, QString PRENOMF,int TELEPHONEF,QString EMAILF, QDateTime DATETIMEF );
    // Méthodes
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(const QString &id);
    QSqlQueryModel* rechercher(const QString &id);
    QSqlQueryModel* trierParDateTime();
    bool enregistrerExcel(const QString &filePath);
    bool modifier(const QString &id, const QString &nom, const QString &prenom, int telephone, const QString &email);
int calculerScore();

// Advanced



public
:
    QString IDENTIFIANTF;
    QString NOMF;
    QString PRENOMF;
    int TELEPHONEF;
    QString EMAILF;
    QDateTime DATETIMEF;
};

#endif // FOURNISEUR_H
