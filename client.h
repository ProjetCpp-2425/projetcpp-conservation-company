#ifndef CLIENT_H
#define CLIENT_H
#include<QString>
#include <QSqlQueryModel>//utilisé pour récupérer et afficher les données de la base.
#include<QTableView>//utilisé pour afficher les données sous forme de tableau.
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

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
    void rechercher(const QString &a, QTableView *g);
    QSqlQueryModel* trierclient(const QString& critere);
    bool exporterPDF();
    int calculerPoints(QString IDENTIFIANT);
    bool remise(QString);

    //QString genererStatistiquesPoints() ;
private:
    int TELEPHONE;
    QString IDENTIFIANT,NOM,PRENOM,EMAIL;

};

#endif // CLIENT_H
