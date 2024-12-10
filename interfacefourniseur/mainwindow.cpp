#include "mainwindow.h"
#include "fourniseur.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent):
     QMainWindow(parent)
     ,ui(new Ui::MainWindow)

{
    ui->setupUi(this);
  ui->tableView->setModel(fourniseur.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_ajouter_clicked()
{
    QString id = ui->lineEdit_identifiant->text();
    QString nom = ui->lineEdit_nom->text();
    QString prenom = ui->lineEdit_prenom->text();
    int tel = ui->lineEdit_telephone->text().toInt();
    QString email = ui->lineEdit_email->text();
    QDateTime datetime = QDateTime::currentDateTime();

    Fourniseur F(id ,nom,  prenom, tel, email, datetime) ;// Assurez-vous que les types correspondent
bool test=F .ajouter();
    if (test) {
        ui->tableView->setModel(fourniseur.afficher());
         QMessageBox::information(nullptr , QObject::tr("ok"), QObject::tr("Ajouter effectue\n""click Cancel to exit"), QMessageBox::Cancel);

     } else {
         QMessageBox::critical(nullptr, QObject::tr("ok"), QObject::tr("ajout non effectue.\n""click Cancel to exit"), QMessageBox::Cancel );
     }
 }


void MainWindow::on_pushButton_supprimer_clicked()
{
    QString id = ui->lineEdit_identifiant->text();
    if (fourniseur.supprimer(id)) {
        QMessageBox::information(nullptr , QObject::tr("ok"), QObject::tr("suppresion effectue\n""click Cancel to exit"), QMessageBox::Cancel);

    } else {
        QMessageBox::critical(nullptr, QObject::tr("ok"), QObject::tr("suppresion non effectue.\n""click Cancel to exit"), QMessageBox::Cancel );
    }
}



void MainWindow::on_pushButton_trier_clicked()
{
    QSqlQueryModel *sortedModel = fourniseur.trierParDateTime();


    ui->tableView->setModel(model);
    QMessageBox::information(this, "Succès", "Fournisseurs triés par date/heure.");
}
void MainWindow::on_pushButton_modifier_clicked()
{
    QString id = ui->lineEdit_identifiant->text();
    QString nom = ui->lineEdit_nom->text();
    QString prenom = ui->lineEdit_prenom->text();
    int tel = ui->lineEdit_telephone->text().toInt();
    QString email = ui->lineEdit_email->text();
    QDateTime datetime = QDateTime::currentDateTime();

    Fourniseur fourniseur(id, nom, prenom, tel, email, datetime);

    if (fourniseur.modifier(id)) {
        QMessageBox::information(this, "Succès", "Fournisseur modifié avec succès.");

    } else {
        QMessageBox::critical(this, "Erreur", "Erreur lors de la modification du fournisseur.");
    }
}

void MainWindow::on_pushButton_enregistrer_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Enregistrer sous", "", "CSV Files (*.csv)");
    if (filePath.isEmpty()) return;

    if (fourniseur.enregistrerExcel(filePath)) {
        QMessageBox::information(this, "Succès", "Données enregistrées dans " + filePath);
    } else {
        QMessageBox::critical(this, "Erreur", "Erreur lors de l'enregistrement des données dans le fichier.");
    }
}
