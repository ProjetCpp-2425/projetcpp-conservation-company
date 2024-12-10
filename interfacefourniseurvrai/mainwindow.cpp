#include "mainwindow.h"
#include "fourniseurs.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QApplication>
#include "QSortFilterProxyModel"
#include <QGroupBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QStandardItemModel>
#include <QStandardItem>

#include <QTimer>


void MainWindow::startScoreCalculationTimer()
{
    // Set up a timer to call calculateScores periodically
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::calculateScores);
    timer->start(5000); // Set interval to 5 seconds (5000 ms)
}



MainWindow::MainWindow(QWidget *parent):
     QMainWindow(parent)
     ,ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    startScoreCalculationTimer(); // Start periodic score calculation
  ui->tableView->setModel(fourniseur.afficher());
  connect(ui->pushButton_statistiques, &QPushButton::clicked, this, &MainWindow::on_pushButton_statistiques_clicked);


  // métiers avancée Notification COntrac

  // Timer setup
  QTimer *timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &MainWindow::onTimerTimeout);
  timer->start(5000); // Trigger every 5 seconds



}



void MainWindow::calculateScores()
{
    QSqlQuery query;
    query.prepare("SELECT IDENTIFIANTF, DATETIMEF, NOMF FROM FOURNISEUR"); // Modify the query to include supplier name

    if (query.exec()) {
        // Create a model to hold the data
        QStandardItemModel *model = new QStandardItemModel(this);
        model->setHorizontalHeaderLabels({"Fournisseur ID", "Nom", "Score"});

        // Populate the model with data
        while (query.next()) {
            QString id = query.value("IDENTIFIANTF").toString();
            QString name = query.value("NOMF").toString();
            QDateTime expirationDate = query.value("DATETIMEF").toDateTime();

            int score = 0;

            // Example logic: if contract is about to expire within 7 days, give a reward
            if (expirationDate <= QDateTime::currentDateTime().addDays(7)) {
                score += 2; // Reward for timely contract renewal
            }

            // Example logic: Late deliveries, high-quality products, etc.
            // Add your conditions to adjust the score here

            // Add supplier data to the model
            QList<QStandardItem*> row;
            row.append(new QStandardItem(id));
            row.append(new QStandardItem(name));
            row.append(new QStandardItem(QString::number(score)));

            model->appendRow(row); // Add the row to the model

            fournisseurScores[id] = score; // Store score for each fournisseur

            qDebug() << "Fournisseur ID: " << id << " Name: " << name << " Score: " << score;
        }

        // Set the model for the table view
        ui->tableView->setModel(model);
    } else {
        qDebug() << "Error executing query: " << query.lastError().text();
    }
}



void MainWindow::updateScoreDisplay()
{
    // Assuming you have a QTableView named tableView
    // Create a QStandardItemModel to display the scores alongside the supplier info

    QStandardItemModel *model = new QStandardItemModel();
    model->setHorizontalHeaderLabels({"ID", "Name", "Score"});

    QMapIterator<QString, int> i(fournisseurScores);
    while (i.hasNext()) {
        i.next();

        QString id = i.key();
        int score = i.value();

        // Add supplier data to the table
        QList<QStandardItem*> row;
        row.append(new QStandardItem(id));
        row.append(new QStandardItem("Supplier Name")); // You can fetch name from the database if needed
        row.append(new QStandardItem(QString::number(score)));

        model->appendRow(row);
    }

    ui->tableView->setModel(model); // Set the model in the table view
}

void MainWindow::onTimerTimeout() {
    checkContractExpirations(); // Delegate the logic to a separate function
}



void MainWindow::checkContractExpirations() {
    QSqlQuery query;
    QDate currentDate = QDate::currentDate();
    QDate expirationDate = currentDate.addDays(7);

    // Use TO_DATE to match Oracle's expected format
    query.prepare("SELECT IDENTIFIANTF, NOMF, DATETIMEF FROM FOURNISEUR "
                  "WHERE DATETIMEF <= TO_DATE(:expirationDate, 'YYYY-MM-DD HH24:MI:SS')");
    query.bindValue(":expirationDate", expirationDate.toString("yyyy-MM-dd") + " 00:00:00");

    if (!query.exec()) {
        qDebug() << "Error querying contract expirations:" << query.lastError().text();
        return;
    }

    // Display notification for each expiring contract
    while (query.next()) {
        QString id = query.value("IDENTIFIANTF").toString();
        QString name = query.value("NOMF").toString();
        QDateTime dateTime = query.value("DATETIMEF").toDateTime();

        QMessageBox::warning(this, "Contract Expiration Alert",
                             QString("Contract for supplier '%1' (ID: %2) is nearing expiration.\n"
                                     "Expiration Date: %3")
                             .arg(name)
                             .arg(id)
                             .arg(dateTime.toString("yyyy-MM-dd HH:mm:ss")));
    }
}









MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_ajouter_clicked()
{
    QString IDENTIFIANTF = ui->lineEdit_identifiant->text();
    QString NOMF= ui->lineEdit_nom->text();
    QString PRENOMF = ui->lineEdit_prenom->text();
    int TELEPHONEF = ui->lineEdit_telephone->text().toInt();
    QString EMAILF = ui->lineEdit_email->text();
    QDateTime DATETIMEF= ui->dateTimeEdit->dateTime();

    Fourniseur F(IDENTIFIANTF,NOMF,  PRENOMF, TELEPHONEF, EMAILF, DATETIMEF) ;// Assurez-vous que les types correspondent
bool test=F .ajouter();
    if (test) {
        ui->tableView->setModel(fourniseur.afficher());
         QMessageBox::information(nullptr , QObject::tr("ok"), QObject::tr("Ajouter effectue\n""click Cancel to exit"), QMessageBox::Cancel);

     } else {
         QMessageBox::critical(nullptr, QObject::tr("ok"), QObject::tr("ajout non effectue.\n""click Cancel to exit"), QMessageBox::Cancel );
     }
    ui->lineEdit_identifiant->clear();
    ui->lineEdit_nom->clear();
    ui->lineEdit_prenom->clear();
    ui->lineEdit_telephone->clear();
    ui->lineEdit_email->clear();

 }


void MainWindow::on_pushButton_supprimer_clicked()
{
    QString identifiant = ui->lineEdit_supprimer->text();
    if (fourniseur.supprimer(identifiant)) {
        QMessageBox::information(this, "Succès", "Suppression effectuée.");
        ui->tableView->setModel(fourniseur.afficher()); // Rafraîchir l'affichage après suppression
    } else {
        QMessageBox::critical(this, "Erreur", "Erreur lors de la suppression.");
    }
}




void MainWindow::on_pushButton_trier_clicked()
{
    QSqlQueryModel* sortedModel = fourniseur.trierParDateTime(); // Récupère le modèle trié
    ui->tableView->setModel(sortedModel); // Met à jour avec le modèle trié
    QMessageBox::information(this, "Succès", "Fournisseurs triés par date/heure.");
}


void MainWindow::on_pushButton_modifier_clicked()
{
    QString identifiant = ui->lineEdit_modifier->text();  // Récupérer l'identifiant

    if (identifiant.isEmpty()) {
        qDebug() << "Identifiant vide !";
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT NOMF, PRENOMF, TELEPHONEF, EMAILF FROM FOURNISEUR WHERE IDENTIFIANTF = :identifiant");
    query.bindValue(":identifiant", identifiant);

    if (query.exec() && query.next()) {
        // Remplir les champs avec les informations actuelles
        ui->lineEdit_nom->setText(query.value("NOMF").toString());
        ui->lineEdit_prenom->setText(query.value("PRENOMF").toString());
        ui->lineEdit_telephone->setText(query.value("TELEPHONEF").toString());
        ui->lineEdit_email->setText(query.value("EMAILF").toString());
    } else {
        qDebug() << "Fournisseur introuvable ou erreur de requête:" << query.lastError().text();
        return;
    }

    // Enregistrer les modifications
    Fourniseur fournisseur;
    QString nom = ui->lineEdit_nom->text();
    QString prenom = ui->lineEdit_prenom->text();
    int telephone = ui->lineEdit_telephone->text().toInt();
    QString email = ui->lineEdit_email->text();

    if (fournisseur.modifier(identifiant, nom, prenom, telephone, email)) {
        qDebug() << "Modification réussie !";
    } else {
        qDebug() << "Échec de la modification !";
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
void MainWindow::on_pushButton_rechercher_clicked()
{
    // Récupérer l'identifiant saisi par l'utilisateur dans la lineEdit
    QString id= ui->lineEdit_rechercher->text();

    // Appeler la méthode rechercher pour obtenir le modèle avec les résultats
    QSqlQueryModel* model = fourniseur.rechercher(id);

    // Vérifier si la recherche a renvoyé un modèle valide
    if (model->rowCount()>0) {
        ui->tableView->setModel(model);  // Mettre à jour le modèle du QTableView
        QMessageBox::information(this, "Succès", "Recherche effectuée avec succès.");
    } else {
        // Si la recherche échoue, afficher un message d'erreur
        QMessageBox::critical(this, "Erreur", "Aucun fournisseur trouvé ou erreur de requête.");
    }
     ui->lineEdit_rechercher->clear();
}

void MainWindow::on_pushButton_statistiques_clicked()
{
    // Query to get the number of suppliers by date
    QSqlQuery query;
    query.prepare("SELECT DATETIMEF, COUNT(*) AS nombre_fournisseurs FROM FOURNISEUR GROUP BY DATETIMEF ORDER BY DATETIMEF");

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", "Erreur lors de la récupération des statistiques: " + query.lastError().text());
        return;
    }

    // Prepare data for the chart
    QBarSet *set = new QBarSet("Fournisseurs");
    QStringList categories; // Dates

    while (query.next()) {
        QString date = query.value(0).toDateTime().toString("yyyy-MM-dd");
        int count = query.value(1).toInt();
        *set << count;
        categories << date;
    }

    // Create a bar series and add the data set
    QBarSeries *series = new QBarSeries();
    series->append(set);

    // Create the chart
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Nombre de fournisseurs par date");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // Set up the X-axis (categories/dates)
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    // Set up the Y-axis (number of suppliers)
    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Nombre de Fournisseurs");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // Create the chart view
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Display the chart in a new window
    QMainWindow *statsWindow = new QMainWindow();
    statsWindow->setCentralWidget(chartView);
    statsWindow->resize(800, 600);
    statsWindow->setWindowTitle("Statistiques des Fournisseurs");
    statsWindow->show();
}





