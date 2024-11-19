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

    void on_line_recherche_textChanged(const QString &arg1);


    //void on_comboBox_currentIndexChanged(int index);
    void on_comboBox_currentIndexChanged(int index);

    void on_exporterPDFButtont_clicked();


    void on_pushButton_8_clicked();

   //void on_push_stat_clicked();

    void on_remise_clicked();
    void sendMail();
    void mailSent(QString status);
    void readyRead();
    void connected();


    void on_push_stat_clicked();

private:
    Ui::MainWindow *ui;//pointeur permet d'accéder aux éléments de l'interface
    client C;
    QStringList files;
    QTcpSocket *socket;

    void afficherDonnees();// Déclaration de la méthode pour afficher les données

};
#endif // MAINWINDOW_H
