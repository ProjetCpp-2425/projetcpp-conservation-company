#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include"QSortFilterProxyModel"
#include "connection.h"
#include <QGroupBox>
#include <QMessageBox>
#include <QSqlQuery>
#include<QIntValidator>
#include <QtPrintSupport/QPrinter>
//#include <QPrinter>
#include <QPainter>
//#include <QPrintDialog>
#include <QtDebug>
#include <QPdfWriter>
#include <QTextStream>
#include<QTextDocument>
//#include <QAbstractSocket>
#include"QSortFilterProxyModel"
#include "smtp.h"
#include "Statwidget.h"
#include <QScreen>
#include <QGuiApplication>

#include <QSerialPort>
#include <QSerialPortInfo>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) ,
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    ui->comboBox->addItem("NOM");
    ui->comboBox->addItem("PRENOM");
    ui->comboBox->addItem("TELEPHONE");

     // Connecter le QComboBox au slot pour gérer le tri
    connect(ui->comboBox, &QComboBox::currentIndexChanged, this, &MainWindow::on_comboBox_currentIndexChanged);

    connect(ui->exporterPDFButtont, &QPushButton::clicked, this, &MainWindow::on_exporterPDFButtont_clicked);

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

    connect(ui->pushButtonSend, SIGNAL(clicked()),this, SLOT(sendMail()));
     connect(ui->pushButtonClear, SIGNAL(clicked()),this, SLOT(close()));


     socket=new QTcpSocket(this);

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
     connect(socket, SIGNAL(connected()), this, SLOT(connected()));
     arduino = new Arduino(this);

         // Connexion du signal dataReceived à un slot pour traiter les données
        // connect(arduino, &Arduino::dataReceived, this, &MainWindow::handleData);
         connect(arduino, &Arduino::clientFound, this, &MainWindow::onClientFound);

         // Vous pouvez aussi essayer d'ouvrir la connexion avec l'Arduino ici si nécessaire
         QString portName = "COM4";  // Remplacez par le nom correct du port
         int baudRate = 9600;        // Le taux de baud par défaut
         if (arduino->openConnection(portName, baudRate)) {
             qDebug() << "Arduino connecté avec succès!";
         } else {
             qDebug() << "Échec de la connexion à l'Arduino.";
         }


}


MainWindow::~MainWindow()
{
    delete ui;

}


//rfid seulement
/*void MainWindow::onClientFound(const QString &UIDC) {
    // Requête pour trouver le client correspondant
    QSqlQuery query;
    // Utilisation de UPPER() pour la comparaison insensible à la casse
    query.prepare("SELECT NOM, EMAIL, TELEPHONE FROM CLIENT WHERE UPPER(UIDC) = UPPER(:UIDC)");
    query.bindValue(":UIDC", UIDC);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la requête : " << query.lastError().text();
        QMessageBox::critical(this, "Erreur", "Impossible de rechercher le client.");
        return;
    }

    if (query.next()) {
        // Client trouvé
        QString clientInfo = QString("Nom : %1\nEMAIL : %2\nTELEPHONE : %3")
                                .arg(query.value(0).toString())
                                .arg(query.value(1).toString())
                                .arg(query.value(2).toString());
        QMessageBox::information(this, "Client trouvé", clientInfo);
    } else {
        // Aucun client trouvé
        QMessageBox::warning(this, "Client introuvable", "Aucun client correspondant trouvé pour cet UIDC.");
    }
}*/

//rfid_servo
/*void MainWindow::onClientFound(const QString &UIDC) {
    // Requête pour trouver le client correspondant
    QSqlQuery query;
    query.prepare("SELECT NOM, EMAIL, TELEPHONE FROM CLIENT WHERE UPPER(UIDC) = UPPER(:UIDC)");
    query.bindValue(":UIDC", UIDC);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la requête : " << query.lastError().text();
        QMessageBox::critical(this, "Erreur", "Impossible de rechercher le client.");
        return;
    }

    if (query.next()) {
        // Client trouvé
        QString clientInfo = QString("Nom : %1\nEMAIL : %2\nTELEPHONE : %3")
                                .arg(query.value(0).toString())
                                .arg(query.value(1).toString())
                                .arg(query.value(2).toString());
        QMessageBox::information(this, "Client trouvé", clientInfo);

        // Envoyer la commande pour ouvrir le servo
        arduino->writeData("OUI\n");
    } else {
        // Aucun client trouvé
        arduino->writeData("NON\n");
        QMessageBox::warning(this, "Client introuvable", "Aucun client correspondant trouvé pour cet UIDC.");

        // Envoyer la commande pour maintenir le servo fermé
    }
}*/

// rfid_servo_lcd

/*void MainWindow::onClientFound(const QString &UIDC) {
    QSqlQuery query;
    query.prepare("SELECT NOM, EMAIL, TELEPHONE FROM CLIENT WHERE UPPER(UIDC) = UPPER(:UIDC)");
    query.bindValue(":UIDC", UIDC);

        if (!query.exec()) {
            qDebug() << "Erreur lors de la requête : " << query.lastError().text();
            QMessageBox::critical(this, "Erreur", "Impossible de rechercher le fournisseur.");
            return;
        }

        if (query.next()) {
            QString clientInfo = QString("NOM: %1\EMAIL: %2\nTELEPHONE: %3")
                                      .arg(query.value(0).toString())
                                      .arg(query.value(1).toString())
                                      .arg(query.value(2).toString());
            QMessageBox::information(this, "Fournisseur trouvé", clientInfo);
             //arduino->writeData("OUI\n");


            // Formatage des données pour l'Arduino
            QString prenom = query.value(0).toString();
            QString telephone = query.value(1).toString();

            // Limitation pour un affichage LCD de 16x2
            prenom = prenom.left(16);
            telephone = telephone.left(16);

            QString lcdMessage = QString("%0,%1\n").arg(prenom).arg(telephone);
            qDebug() << "Message envoyé à Arduino : " << lcdMessage;
            arduino->writeData(lcdMessage.toUtf8());
        } else {
            QMessageBox::warning(this, "Fournisseur introuvable", "Aucun fournisseur trouvé pour cet UIDC.");
            //arduino->writeData("NON\n");
            arduino->writeData("UNKNOWN\n");
        }

}*/
void MainWindow::onClientFound(const QString &UIDC) {
    QSqlQuery query;
    query.prepare("SELECT NOM, EMAIL, TELEPHONE FROM CLIENT WHERE UPPER(UIDC) = UPPER(:UIDC)");
    query.bindValue(":UIDC", UIDC);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la requête : " << query.lastError().text();
        QMessageBox::critical(this, "Erreur", "Impossible de rechercher le fournisseur.");
        return;
    }

    if (query.next()) {
        QString clientInfo = QString("NOM: %1\nEMAIL: %2\nTELEPHONE: %3")
                                  .arg(query.value(0).toString())
                                  .arg(query.value(1).toString())
                                  .arg(query.value(2).toString());
        QMessageBox::information(this, "Fournisseur trouvé", clientInfo);

        // Formatage des données pour l'Arduino
        QString prenom = query.value(1).toString();
        QString telephone = query.value(2).toString();

        // Limitation pour un affichage LCD de 16x2
        prenom = prenom.left(16);
        telephone = telephone.left(16);

        QString lcdMessage = QString("%1,%2\n").arg(prenom).arg(telephone);
        qDebug() << "Message envoyé à Arduino : " << lcdMessage;
        arduino->writeData(lcdMessage.toUtf8());
    } else {
        QMessageBox::warning(this, "Fournisseur introuvable", "Aucun fournisseur trouvé pour cet UIDC.");
        arduino->writeData("UNKNOWN\n");
    }
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


void MainWindow::on_exporterPDFButtont_clicked()
{
    client c;
        if (c.exporterPDF()) {
            QMessageBox::information(this, "Exportation PDF", "Le fichier PDF a été créé avec succès.");
        } else {
            QMessageBox::warning(this, "Erreur", "Impossible de créer le fichier PDF.");
        }
}




void MainWindow::on_pushButton_8_clicked()
{
    QString id;
    id=ui->idforpoints->text();
    int aux=C.calculerPoints(id);
    ui->tab_client->setModel(C.afficher());
    QString s = QString::number(aux);
}



/*void MainWindow::on_push_stat_clicked()
{

    client C;
        try{
            QT_CHARTS_USE_NAMESPACE
            QChart *chart = new QChart();
            QBarSeries *series = new QBarSeries();
            QBarCategoryAxis *axis = new QBarCategoryAxis();

            QBarSet *set = new QBarSet(" Point de fidelite");
            QStringList typesList;
            QList<QBarSet *> nbrList;
            std::map<QString , int> list = C.statNbrPerType();
            for(auto itr = list.begin() ; itr != list.end(); itr++) {
                typesList.append(itr->first);
    //            nbrList.append(itr->second);
                *set << itr->second;
                nbrList.append(set);
            }
            qDebug() << typesList;
            series->append(set);
            chart->addSeries(series);
            chart->setAnimationOptions(QChart::AllAnimations);
            axis->append(typesList);
            chart->createDefaultAxes();
            chart->setAxisX(axis, series);
            chart->legend()->setAlignment(Qt::AlignBottom);
            QChartView *chartView = new QChartView(chart);
            chartView->setRenderHint(QPainter::Antialiasing);
            QPalette pal = qApp->palette();
            pal.setColor(QPalette::Window, QRgb(0x0d4261));
            pal.setColor(QPalette::WindowText, QRgb(0x95212c));
            qApp->setPalette(pal);
            QFont font;
            font.setPixelSize(40);
            chart->setTitleFont(font);
            chart->setTitleBrush(QBrush(Qt::red));
            chart->setTitle("statistique Point fidelite PER CIN");
            chartView->setChart(chart);
            chartView->showNormal();



        }catch(...){

}

}
*/


void MainWindow::on_remise_clicked()
{
    QString id;

            id=ui->idforpoints->text();
            int aux=C.calculerPoints(id);
            aux=aux*10;
             QString s = QString::number(aux);


            bool test=C.remise(id);

            if(test){
                QMessageBox::information(nullptr, QObject::tr("database is open"),
                            QObject::tr("remise successful.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);


            }
            else

            {

                QMessageBox::information(nullptr, QObject::tr("database is open"),
                            QObject::tr("remise failed.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);


            }
            ui->tab_client->setModel(C.afficher());

}

void MainWindow::sendMail()
{
    smtp* smtpClient = new smtp(ui->lineEditEmailCredentials->text(), ui->lineEditPasswordCredentials->text(), ui->lineEditHost->text(), ui->lineEditPort->text().toInt());
    connect(smtpClient, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


    if( !files.isEmpty() )
        smtpClient->sendMail(ui->lineEditEmailCredentials->text(), ui->lineEditEmailTo->text() , ui->lineEditSubject->text(),ui->lineEdit->text(), files );
    else
        smtpClient->sendMail(ui->lineEditEmailCredentials->text(), ui->lineEditEmailTo->text() , ui->lineEditSubject->text(),ui->lineEdit->text());
}


void MainWindow::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}

void MainWindow::readyRead() {
    qDebug() << "Données prêtes à être lues.";
}

void MainWindow::connected() {
    qDebug() << "Connecté au serveur.";
}



void MainWindow::on_push_stat_clicked()
{
    QMap<QString, int> stats;

    // Initialiser les tranches spécifiques
    stats["0"] = 0;
    stats["1-10"] = 0;
    stats["11-20"] = 0;
    stats["21-30"] = 0;
    stats["31-40"] = 0;
    stats["41-50"] = 0;


    QSqlQuery query("SELECT pointsf FROM client");
    while (query.next()) {
        int points = query.value(0).toInt();

        if (points == 0) { // Points égaux à 0
            stats["0"]++;
        } else if (points <= 10) { // Points entre 1 et 25
            stats["1-10"]++;
        } else if (points <= 20) { // Points entre 26 et 50
            stats["11-20"]++;
        } else if (points <= 30) { // Points entre 51 et 75
            stats["21-30"]++;
        } else if (points <= 40) { // Points entre 76 et 100
            stats["31-40"]++;
        }
        else if (points <= 50) { // Points entre 76 et 100
                    stats["41-50"]++;
                }
    }

    // Vérifier si aucune donnée n'existe pour toutes les tranches
    bool hasData = false;
    for (int value : stats.values()) {
        if (value > 0) {
            hasData = true;
            break;
        }
    }
    if (!hasData) {
        QMessageBox::warning(this, "Statistiques", "Aucune donnée à afficher !");
        return;
    }

    // Créer la fenêtre et afficher les statistiques
    QDialog *statWindow = new QDialog(this);
    StatWidget *statWidget = new StatWidget(statWindow);
    statWidget->setStatistics(stats);

    statWindow->setWindowTitle("Statistiques des points (détails)");
    statWindow->resize(400, 400); // Taille augmentée

    // Ajuster le widget à la taille de la fenêtre
    statWidget->setGeometry(0, 0, statWindow->width(), statWindow->height());

    // Centrer la fenêtre avec QScreen
    QScreen *screen = QGuiApplication::primaryScreen();
    if (screen) {
        QRect screenGeometry = screen->geometry();
        QPoint center = screenGeometry.center();
        statWindow->move(center.x() - statWindow->width() / 2, center.y() - statWindow->height() / 2);
    }

    statWindow->show();
}









