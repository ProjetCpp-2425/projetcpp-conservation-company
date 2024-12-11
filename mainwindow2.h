#ifndef MAINWINDOW2_H
#define MAINWINDOW2_H
#include <QMainWindow>
#include <QPushButton>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QUrlQuery>
#include <QMainWindow>
#include "statestiques.h"
#include "connection.h"
#include <QMainWindow>
#include <QPushButton>
#include "mainwindow.h"
#include "mainwindow3.h"


#include <QSqlTableModel>
class MainWindow;
class MainWindow3; // Déclaration anticipée

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow2;
}
QT_END_NAMESPACE
class MainWindow2 : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow2(QWidget *parent = nullptr);
    ~MainWindow2();
    void setupTable();
    void afficherProduits();


private slots:
    void on_on_btnAjouterProduit_clicked_clicked();  // For adding product
    void on_pushButton_clicked();  // For delete functionality
    void on_exportButton_clicked();  // For export functionality
    void on_buyButton_clicked();  // For buy button action
    void on_searchButton_clicked();  // For search functionality
    void on_triButton_clicked();  // For sorting functionality
    void on_stat_clicked();  // For statistics button
    void on_update_button_clicked();
    void on_tableWidget_cellClicked(int row);
   //void readyRead();             // Slot pour lire les données Arduino
    //void connected();
     void on_actionShowCommands_triggered(); // Ajouter une action pour afficher les commandes
     void on_actionShowCommands_clicked();
        void viewHistory();      // Voir l'historique des changements
        void createDirectory();

        void on_pushButton_2_clicked();

        void on_pushButton_3_clicked();

private:
    Ui::MainWindow2 *ui;
    QPushButton *preferencesButton;  // Button to trigger preferences actions
    QPushButton *Preferences;
    MainWindow *window;
    MainWindow3 *window3;// Instance de MainWindow2


       QString arduinoPortName;      // Nom du port série
       //void setupArduino();          // Méthode d'initialisation Arduino
      // void readFromArduino();       // Lecture des données Arduino
      // void handleUID(const QString &UIDC);
       //void handleData(const QByteArray &data);
       // Traitement des données Arduino (exemple : UID)
       //void checkClientByUID(const QString &UIDC);
       //void onClientFound(const QString &UIDC);

        QSqlTableModel *model; // Modèle pour connecter la base de données au TableView
};

#endif


