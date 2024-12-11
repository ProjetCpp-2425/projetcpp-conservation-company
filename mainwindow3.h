#ifndef MAINWINDOW3_H
#define MAINWINDOW3_H


#include <QMainWindow>
#include <QSqlQueryModel>
#include <QTableView>
#include "fourniseurs.h"
#include "mainwindow.h"
#include "mainwindow2.h"


QT_BEGIN_NAMESPACE
class MainWindow;
class MainWindow2; // Déclaration anticipée
// Déclaration anticipée

namespace Ui {
class MainWindow3;
}
QT_END_NAMESPACE
class MainWindow3 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow3(QWidget *parent = nullptr);
    ~MainWindow3();
private slots:
    void on_pushButton_ajouter_clicked();
    void on_pushButton_supprimer_clicked();
 void on_pushButton_modifier_clicked();
    void on_pushButton_trier_clicked();
    void on_pushButton_enregistrer_clicked();
void on_pushButton_rechercher_clicked();
//void on_pushButton_statistiques_clicked();



// métiers avancée Notification

void checkContractExpirations(); // Slot to check expiration dates
void onTimerTimeout(); // Slot for handling QTimer timeouts

void calculateScores();
void updateScoreDisplay();
void startScoreCalculationTimer(); // Declare the timer start function

void on_pushButtonB_clicked();

void on_pushButton_2_clicked();

private:
    Ui::MainWindow3 *ui;
    Fourniseur fourniseur;
    QSqlQueryModel *model;
    QSet<QString> notifiedContracts; // Track notified contract IDs
    QMap<QString, int> fournisseurScores; // Stores scores for each fournisseur
    MainWindow *window;
    MainWindow2 *window2;


};


#endif
