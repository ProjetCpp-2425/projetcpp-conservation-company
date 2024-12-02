#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QComboBox>
#include <QMainWindow>
#include "client.h"
#include <QWidget>
#include <QPainter>
#include <QString>
#include <QMap>
#include <QDebug>
#include <map>
#include "smtp.h"
#include "arduino.h"
#include <QMessageBox>
#include <QSerialPort>
#include <QSqlQuery>

namespace Ui { class MainWindow; }
QT_BEGIN_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_sup_clicked();
    void on_pb_modif_clicked();
    void onClientSelected(const QModelIndex &index);
    void remplirIdentifiant(const QModelIndex &index);
    void on_line_recherche_textChanged(const QString &arg1);
    void on_comboBox_currentIndexChanged(int index);
    void on_exporterPDFButtont_clicked();
    void on_pushButton_8_clicked();
    void on_push_stat_clicked();
    void on_remise_clicked();
    void sendMail();
    void mailSent(QString status);
    void readyRead();             // Slot pour lire les données Arduino
    void connected();             // Slot pour vérifier la connexion Arduino
    //void onClientFound(const QString &uid);  // Traite l'UID reçu


private:
    Ui::MainWindow *ui;           // Pointeur vers l'interface graphique
    client C;
    QStringList files;
    QTcpSocket *socket;
    Arduino *arduino;  // Déclarez un objet Arduino pour gérer la communication

    void afficherDonnees();       // Méthode pour afficher les données
    QString arduinoPortName;      // Nom du port série
    void setupArduino();          // Méthode d'initialisation Arduino
    void readFromArduino();       // Lecture des données Arduino
    void handleUID(const QString &UIDC);
    void handleData(const QByteArray &data);
    // Traitement des données Arduino (exemple : UID)
    //void checkClientByUID(const QString &UIDC);
    void onClientFound(const QString &UIDC);


};

QT_END_NAMESPACE
#endif // MAINWINDOW_H
