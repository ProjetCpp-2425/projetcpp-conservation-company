#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include <QTableView>
#include "fourniseurs.h"
#include<QString>
#include <QSet>




QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
   explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_ajouter_clicked();
    void on_pushButton_supprimer_clicked();
 void on_pushButton_modifier_clicked();
    void on_pushButton_trier_clicked();
    void on_pushButton_enregistrer_clicked();
void on_pushButton_rechercher_clicked();
void on_pushButton_statistiques_clicked();



// métiers avancée Notification

void checkContractExpirations(); // Slot to check expiration dates
void onTimerTimeout(); // Slot for handling QTimer timeouts

void calculateScores();
void updateScoreDisplay();
void startScoreCalculationTimer(); // Declare the timer start function



private:
    Ui::MainWindow *ui;
    Fourniseur fourniseur;
    QSqlQueryModel *model;
QSet<QString> notifiedContracts; // Track notified contract IDs

QMap<QString, int> fournisseurScores; // Stores scores for each fournisseur


};

#endif // MAINWINDOW_H

