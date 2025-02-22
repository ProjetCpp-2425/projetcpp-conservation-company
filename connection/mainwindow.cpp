#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "client.h"
#include"QSortFilterProxyModel"
#include <QGroupBox>
#include "connection.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) ,
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->comboBox->addItem("NOM");
    ui->comboBox->addItem("PRENOM");
    ui->comboBox->addItem("TELEPHONE");

        // Connecter le QComboBox au slot pour gérer le tri
    connect(ui->comboBox, &QComboBox::currentIndexChanged, this, &MainWindow::on_comboBox_currentIndexChanged);
    QRegularExpression regexTelephone("^\\d{8}$");  // Regex pour 8 chiffres uniquement
    ui->line_tel->setValidator(new QRegularExpressionValidator(regexTelephone, this));

    QRegularExpression regexIdentifiant("^[A-Za-z0-9]+$");  // Lettres et chiffres uniquement
    ui->line_id->setValidator(new QRegularExpressionValidator(regexIdentifiant, this));

    QRegularExpression regexText("^[A-Za-zÀ-ÿ\\s]+$");  // Lettres avec accents et espaces
    ui->line_nom->setValidator(new QRegularExpressionValidator(regexText, this));
    ui->line_prenom->setValidator(new QRegularExpressionValidator(regexText, this));

    QRegularExpression regexEmail("^[\\w\\.-]+@[\\w-]+(\\.[\\w-]+)*\\.[A-Za-z]{2,}$");
    ui->line_mail->setValidator(new QRegularExpressionValidator(regexEmail, this));
    connect(ui->tab_client, &QTableView::clicked, this, &MainWindow::onClientSelected);
    connect(ui->tab_client, &QTableView::clicked, this, &MainWindow::remplirIdentifiant);



    connection conn;
    if (!conn.createconnect()) {
        qDebug() << "Erreur : Connexion à la base de données échouée.";
        QMessageBox::critical(this, "Erreur de connexion", "Impossible de se connecter à la base de données.");
        return;
    }
    ui->tab_client->setModel(C.afficher());
    connect(ui->line_recherche, &QLineEdit::textChanged, this, &MainWindow::on_line_recherche_textChanged);


}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    int TELEPHONE = ui->line_tel->text().toInt();
    QString NOM = ui->line_nom->text();
    QString PRENOM = ui->line_prenom->text();
    QString EMAIL = ui->line_mail->text();
    QString IDENTIFIANT = ui->line_id->text();
    if (!EMAIL.contains('@')) {
            // Si l'email est invalide, afficher un message d'erreur et ne pas ajouter
            QMessageBox::warning(this, "Erreur Email", "L'email doit contenir un '@'. L'ajout est impossible.");
            return;
        }
    // Vérifier si un champ est vide
    if (NOM.isEmpty() || PRENOM.isEmpty() || EMAIL.isEmpty() || IDENTIFIANT.isEmpty() || ui->line_tel->text().isEmpty()) {
        QMessageBox::warning(nullptr, QObject::tr("Champ(s) vide(s)"),
                             QObject::tr("Veuillez remplir tous les champs avant d'ajouter le client."),
                             QMessageBox::Ok);
    } else {
        client C(IDENTIFIANT, NOM, PRENOM, EMAIL, TELEPHONE);
        bool test = C.ajouter();

        if (test) {
            QMessageBox::information(nullptr, QObject::tr("OK"),
                                     QObject::tr("Ajout effectué.\n"
                                                 "Click Cancel to exit."), QMessageBox::Cancel);
            ui->tab_client->setModel(C.afficher());
            if (!ui->line_tel->text().isEmpty() ||
                !ui->line_nom->text().isEmpty() ||
                !ui->line_prenom->text().isEmpty() ||
                !ui->line_mail->text().isEmpty() ||
                !ui->line_id->text().isEmpty() ||
                 !ui->lineEdit_sup->text().isEmpty()   )
            {
                ui->line_tel->clear();
                ui->line_nom->clear();
                ui->line_prenom->clear();
                ui->line_mail->clear();
                ui->line_id->clear();
                ui->lineEdit_sup->clear();
            }
        } else {
            QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                  QObject::tr("Ajout non effectué.\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);
        }
    }



}


void MainWindow::on_pushButton_sup_clicked()
{

    QString identifiant = ui->lineEdit_sup->text();

    if (identifiant.isEmpty()) {
        QMessageBox::warning(nullptr, QObject::tr("Attention"),
                             QObject::tr("Veuillez sélectionner un identifiant à supprimer."), QMessageBox::Cancel);
        return;
    }

    client C;
    C.setIDENTIFIANT(identifiant);
    bool test = C.supprimer(C.getIDENTIFIANT());

    if (test) {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Suppression réussie.\nClick Cancel to exit."), QMessageBox::Cancel);
        ui->tab_client->setModel(C.afficher()); // Mettre à jour la table après la suppression
        ui->lineEdit_sup->clear(); // Effacer le champ identifiant après suppression
        ui->line_tel->clear();
        ui->line_nom->clear();
        ui->line_prenom->clear();
        ui->line_mail->clear();
        ui->line_id->clear();
        ui->line_id->setReadOnly(false);


    } else {
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                              QObject::tr("Échec de la suppression.\nClick Cancel to exit."), QMessageBox::Cancel);
    }

}

void MainWindow::remplirIdentifiant(const QModelIndex &index)
{
    // Récupère l'identifiant de la ligne sélectionnée (assume que l'identifiant est dans la première colonne)
    QString identifiant = ui->tab_client->model()->data(ui->tab_client->model()->index(index.row(), 0)).toString();

    // Remplit le champ lineEdit_sup avec l'identifiant sélectionné
    ui->lineEdit_sup->setText(identifiant);
}

void MainWindow::onClientSelected(const QModelIndex &index) {
    // Récupère l'identifiant du client sélectionné
    QString clientID = ui->tab_client->model()->data(index).toString();

    // Préparez une requête pour récupérer les informations du client depuis la base de données
    QSqlQuery query;
    query.prepare("SELECT NOM, PRENOM, EMAIL, TELEPHONE FROM Client WHERE IDENTIFIANT = :IDENTIFIANT");
    query.bindValue(":IDENTIFIANT", clientID);

    if (query.exec() && query.next()) {
        // Remplir les champs de l'interface avec les données du client
        ui->line_nom->setText(query.value("NOM").toString());
        ui->line_prenom->setText(query.value("PRENOM").toString());
        ui->line_mail->setText(query.value("EMAIL").toString());
        ui->line_tel->setText(query.value("TELEPHONE").toString());
        ui->line_id->setText(clientID);  // Remplir aussi l'identifiant

        ui->line_id->setReadOnly(true);

    } else {
        qDebug() << "Erreur lors de la récupération des informations du client:" << query.lastError().text();
    }
}


void MainWindow::on_pb_modif_clicked()
{

    client C2;
    int TELEPHONE = ui->line_tel->text().toInt();
    QString NOM = ui->line_nom->text();
    QString PRENOM = ui->line_prenom->text();
    QString EMAIL = ui->line_mail->text();
    QString IDENTIFIANT = ui->line_id->text();

    // Vérification des champs vides
    if (NOM.isEmpty() || PRENOM.isEmpty() || EMAIL.isEmpty() || IDENTIFIANT.isEmpty() || ui->line_tel->text().isEmpty()) {
        QMessageBox::warning(this, QObject::tr("Champs vides"),
                             QObject::tr("Veuillez remplir tous les champs."),
                             QMessageBox::Ok);
        return; // Sortie de la fonction si un champ est vide
    }
    if (!EMAIL.contains('@')) {
            QMessageBox::warning(this, QObject::tr("Email invalide"),
                                 QObject::tr("L'email doit contenir un '@'. La modification est impossible."),
                                 QMessageBox::Ok);
            return; // Empêche la modification si l'email est invalide
        }
    // Si tous les champs sont remplis, procéder à la modification
    bool test = C2.Modifier(IDENTIFIANT, NOM, PRENOM, EMAIL, TELEPHONE);
    if (test) {
        QMessageBox::information(this, QObject::tr("OK"),
                                 QObject::tr("Modification réussie.\n"
                                             "Cliquez sur Annuler pour fermer."), QMessageBox::Cancel);
        ui->tab_client->setModel(C2.afficher());
        ui->line_id->setReadOnly(false);

            if (!ui->line_tel->text().isEmpty() ||
                !ui->line_nom->text().isEmpty() ||
                !ui->line_prenom->text().isEmpty() ||
                !ui->line_mail->text().isEmpty() ||
                !ui->line_id->text().isEmpty() ||
                 !ui->lineEdit_sup->text().isEmpty()   )
            {
                ui->line_tel->clear();
                ui->line_nom->clear();
                ui->line_prenom->clear();
                ui->line_mail->clear();
                ui->line_id->clear();
                ui->lineEdit_sup->clear();
            }
    } else {
        QMessageBox::critical(this, QObject::tr("Échec"),
                              QObject::tr("La modification a échoué.\n"
                                          "Cliquez sur Annuler pour fermer."), QMessageBox::Cancel);
    }



    }




void MainWindow::on_line_recherche_textChanged(const QString &text)
{
    // Si le champ est vide, afficher tous les clients
     if (text.isEmpty()) {
         client C;
         ui->tab_client->setModel(C.afficher());
         return;
     }

     // Appel à la méthode rechercher pour mettre à jour le tableau avec les résultats
     client C;
     C.rechercher(text, ui->tab_client);
}




void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    QString critere;

        // Obtenir le critère sélectionné dans le QComboBox
        if (index == 0) {
            critere = "NOM";
        } else if (index == 1) {
            critere = "PRENOM";
        } else if (index == 2) {
            critere = "TELEPHONE";
        }

        // Appeler la fonction de tri depuis la classe `client`
        client c;
        QSqlQueryModel *model = c.trierclient(critere);

        // Afficher le résultat du tri dans la vue
        ui->tab_client->setModel(model);
}

