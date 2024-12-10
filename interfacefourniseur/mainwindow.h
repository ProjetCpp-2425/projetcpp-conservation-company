#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include <QTableView>
#include "fourniseur.h"

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

private:
    Ui::MainWindow *ui;
    Fourniseur fourniseur;
    QSqlQueryModel *model;


};

#endif // MAINWINDOW_H

