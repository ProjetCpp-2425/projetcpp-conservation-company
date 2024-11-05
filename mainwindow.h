#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "client.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_sup_clicked();
    void on_pb_modif_clicked();
    void onClientSelected(const QModelIndex &index);
    void remplirIdentifiant(const QModelIndex &index);


private:
    Ui::MainWindow *ui;
    client C;
    void afficherDonnees();               // Déclaration de la méthode pour afficher les données

};
#endif // MAINWINDOW_H
