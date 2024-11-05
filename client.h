#ifndef CLIENT_H
#define CLIENT_H
#include<QString>
#include <QSqlQueryModel>//utilisé pour récupérer et afficher les données de la base.
#include<QTableView>//utilisé pour afficher les données sous forme de tableau.
class client
{
public:
    client();
    client(QString,QString ,QString ,QString , int );
    int getTELEPHONE();
    QString getNOM();
    QString getPRENOM();
    QString getEMAIL();
    QString getIDENTIFIANT();
    void setTELEPHONE(int);
    void setNOM(QString);
    void setPRENOM(QString);
    void setEMAIL(QString);
    void setIDENTIFIANT(QString);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(QString);
    bool Modifier(QString,QString,QString ,QString,int);


private:
    int TELEPHONE;
    QString IDENTIFIANT,NOM,PRENOM,EMAIL;

};

#endif // CLIENT_H
