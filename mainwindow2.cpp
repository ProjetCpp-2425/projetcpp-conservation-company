#include "mainwindow2.h"
#include "ui_mainwindow2.h"
#include "produit.h"
#include <QMessageBox>
#include <QDebug>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QUrlQuery>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDate>
#include <QScreen>
#include "statestiques.h"
#include <QScreen>
#include <QGuiApplication>
#include <QMessageBox>
#include <QDialog>
#include <QVBoxLayout>
#include <QSqlQuery>
#include <QScreen>
#include <QGuiApplication>
#include <QMessageBox>
#include <QDialog>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlQuery>
#include <QVBoxLayout>
#include "statestiques.h"
#include "connection.h"
#include "historymanager.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QDir>
MainWindow2::MainWindow2(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow2)
{
    ui->setupUi(this);
    setupTable();
    afficherProduits();
    connect(ui->btnViewHistory, &QPushButton::clicked, this, &MainWindow2::viewHistory);


        }

void MainWindow2::setupTable() {
    // Set up table widget columns and headers
    ui->tableWidget->setColumnCount(5);
    QStringList headers;
    headers << "Nom" << "Code Barres" << "Type" << "Quantité" << "Date";
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    // Customize table properties
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Set column sizes
    ui->tableWidget->setColumnWidth(0, 150); // Nom
    ui->tableWidget->setColumnWidth(1, 150); // Code Barres
    ui->tableWidget->setColumnWidth(2, 150); // Type
    ui->tableWidget->setColumnWidth(3, 100); // Quantité
    ui->tableWidget->setColumnWidth(4, 120); // Date

    // Set header style
    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color: #E0E0E0; }");

    // Enable alternating row colors
    ui->tableWidget->setAlternatingRowColors(true);
}

void MainWindow2::on_on_btnAjouterProduit_clicked_clicked()
{
    QString nom = ui->lineEdit_nom->text();
    QString code_barres = ui->lineEdit_code->text();
    QString type = ui->lineEdit_type->text();
    int quantite = ui->lineEdit_quantite->value(); // Assumé comme QSpinBox
    QString date_produit = ui->lineEdit_date->date().toString("yyyy-MM-dd"); // Assumé comme QDateEdit

    // Validation des champs vides
    if (nom.isEmpty() || code_barres.isEmpty() || type.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Tous les champs doivent être remplis !");
        return;
    }

    // Validation de la quantité
    if (quantite <= 0) {
        QMessageBox::warning(this, "Erreur", "La quantité doit être supérieure à 0 !");
        return;
    }

    // Vérification du code-barres existant
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM PRODUITS WHERE code_barres = :code_barres");
    checkQuery.bindValue(":code_barres", code_barres);

    if (!checkQuery.exec()) {
        qDebug() << "Erreur lors de la vérification du code-barres :" << checkQuery.lastError().text();
        QMessageBox::critical(this, "Erreur", "Erreur lors de la vérification du code-barres.");
        return;
    }

    if (checkQuery.next() && checkQuery.value(0).toInt() > 0) {
        QMessageBox::warning(this, "Erreur", "Ce code-barres existe déjà !");
        return;
    }

    // Création et ajout du produit
    Produit nouveauProduit(nom, code_barres, type, quantite, date_produit);

    if (nouveauProduit.ajouter()) {
        QMessageBox::information(this, "Succès", "Produit ajouté avec succès !");
        // Réinitialisation des champs
        ui->lineEdit_nom->clear();
        ui->lineEdit_code->clear();
        ui->lineEdit_type->clear();
        ui->lineEdit_quantite->setValue(1); // Valeur par défaut
        ui->lineEdit_date->setDate(QDate::currentDate());

        // Rafraîchir la table des produits
        afficherProduits();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout du produit.");
    }
}


void MainWindow2::afficherProduits() {
    qDebug() << "Starting afficherProduits()";

    QSqlQuery query;
    query.prepare("SELECT nom, code_barres, type, quantite, date_produit FROM PRODUITS ORDER BY nom");

    if (!query.exec()) {
        qDebug() << "Query Error:" << query.lastError().text();
        return;
    }

    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    int row = 0;
    while (query.next()) {
        qDebug() << "Processing row" << row;

        ui->tableWidget->insertRow(row);

        // Create and set items for each column
        for (int col = 0; col < 5; col++) {
            QTableWidgetItem *item = new QTableWidgetItem();

            // Format date for the date column
            if (col == 4) {
                QDate date = query.value(col).toDate();
                item->setText(date.toString("dd/MM/yyyy"));
            } else {
                item->setText(query.value(col).toString());
            }

            // Center align the text
            item->setTextAlignment(Qt::AlignCenter);

            ui->tableWidget->setItem(row, col, item);

            qDebug() << "Column" << col << ":" << item->text();
        }
        row++;
    }

    qDebug() << "Total rows processed:" << row;
}

void MainWindow2::on_pushButton_clicked() {
    QString code_barres = ui->lineEdit_8->text();

    if (code_barres.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un code-barres.");
        return;
    }

    if (Produit::supprimer(code_barres)) {
        QMessageBox::information(this, "Succès", "Produit supprimé avec succès !");
        ui->lineEdit_8->clear();
        afficherProduits();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la suppression du produit.");
    }
}

void MainWindow2::on_exportButton_clicked()
{
    // File selection for saving the PDF
    QString filePath = QFileDialog::getSaveFileName(this, "Exporter en PDF", "", "PDF Files (*.pdf)");
    if (filePath.isEmpty())
        return;

    if (!filePath.endsWith(".pdf", Qt::CaseInsensitive)) {
        filePath += ".pdf";
    }

    QPdfWriter pdfWriter(filePath);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setTitle("Exportation des Produits");
    pdfWriter.setResolution(300);

    QPainter painter(&pdfWriter);
    int margin = 30;
    int y = margin;

    // Title
    QFont titleFont("Helvetica", 14, QFont::Bold);
    painter.setFont(titleFont);
    painter.drawText(margin, y, "Liste des Produits");
    y += 100;

    // Column headers
    QStringList headers = {"Nom", "Code Barres", "Type", "Quantité", "Date"};
    QFont headerFont("Helvetica", 10, QFont::Bold);
    painter.setFont(headerFont);

    int colPositions[] = {margin, margin + 300, margin + 600, margin + 900, margin + 1200}; // Column positions
    for (int i = 0; i < headers.size(); ++i) {
        painter.drawText(colPositions[i], y, headers[i]);
    }

    y += 50;

    // Add a horizontal line below headers
    painter.drawLine(margin, y, pdfWriter.width() - margin, y);
    y += 50;

    // Prepare a 2D array for data rows
    QVector<QVector<QString>> tableData;

    QSqlQuery query;
    query.prepare("SELECT nom, code_barres, type, quantite, date_produit FROM PRODUITS ORDER BY nom");

    if (query.exec()) {
        while (query.next()) {
            QVector<QString> row;
            row.append(query.value(0).toString()); // Nom
            row.append(query.value(1).toString()); // Code Barres
            row.append(query.value(2).toString()); // Type
            row.append(query.value(3).toString()); // Quantité
            row.append(query.value(4).toDate().toString("dd/MM/yyyy")); // Date
            tableData.append(row);
        }
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'exportation : " + query.lastError().text());
        return;
    }

    // Display rows from the 2D array
    QFont contentFont("Helvetica", 9);
    painter.setFont(contentFont);

    for (const auto &row : tableData) {
        for (int col = 0; col < row.size(); ++col) {
            painter.drawText(colPositions[col], y, row[col]);
        }
        y += 50;

        // Add a line between rows for better readability
        painter.drawLine(margin, y, pdfWriter.width() - margin, y);
        y += 50;

        // Check for page overflow and add a new page if necessary
        if (y > pdfWriter.height() - margin) {
            pdfWriter.newPage();
            y = margin + 50; // Adjust y for the new page
            painter.setFont(headerFont);
            for (int i = 0; i < headers.size(); ++i) {
                painter.drawText(colPositions[i], y, headers[i]);
            }
            y += 50;
            painter.drawLine(margin, y, pdfWriter.width() - margin, y);
            y += 50;
            painter.setFont(contentFont);
        }
    }

    painter.end();
    QMessageBox::information(this, "Succès", "Produits exportés avec succès en PDF !");
}

void MainWindow2::on_buyButton_clicked()
{
    QString barcode = ui->buyBarreCode->text();
    int requestedQuantity = ui->buyQuantity->value(); // Assuming buyQuantity is a QSpinBox or similar numeric input

    // Validate inputs
    if (barcode.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un code-barres.");
        return;
    }
    if (requestedQuantity <= 0) {
        QMessageBox::warning(this, "Erreur", "La quantité demandée doit être supérieure à 0.");
        return;
    }

    // Query the product using the barcode
    QSqlQuery query; // Utilisation de QSqlQuery au lieu de QUrlQuery
    query.prepare("SELECT nom, quantite FROM PRODUITS WHERE code_barres = :barcode");
    query.bindValue(":barcode", barcode);

    if (!query.exec() || !query.next()) {
        QMessageBox::critical(this, "Erreur", "Produit introuvable. Vérifiez le code-barres.");
        return;
    }

    QString productName = query.value(0).toString();
    int stockQuantity = query.value(1).toInt();

    // Compare quantities
    if (stockQuantity >= requestedQuantity) {
        // Update the database
        QSqlQuery updateQuery; // Nouvelle requête pour mise à jour
        updateQuery.prepare("UPDATE PRODUITS SET quantite = quantite - :requestedQuantity WHERE code_barres = :barcode");
        updateQuery.bindValue(":requestedQuantity", requestedQuantity);
        updateQuery.bindValue(":barcode", barcode);

        if (updateQuery.exec()) {
            QMessageBox::information(this, "Succès",
                                      QString("Achat réussi pour le produit '%1'.\nQuantité achetée: %2.")
                                      .arg(productName)
                                      .arg(requestedQuantity));
            afficherProduits(); // Refresh the table to show updated stock
        } else {
            QMessageBox::critical(this, "Erreur", "Échec de la mise à jour du stock.");
        }
    } else {
        QMessageBox::warning(this, "Erreur",
                              QString("Stock insuffisant pour le produit '%1'.\nStock disponible: %2, demandé: %3.")
                              .arg(productName)
                              .arg(stockQuantity)
                              .arg(requestedQuantity));
    }
}


void MainWindow2::on_searchButton_clicked()
{
    QString searchTerm = ui->search->text().trimmed(); // Récupère le terme de recherche

    // Si le champ de recherche est vide, on affiche tous les produits
    if (searchTerm.isEmpty()) {
        afficherProduits();  // Appel de la fonction pour afficher tous les produits
        return;
    }

    QString queryStr;

    // Vérifie si le terme est composé uniquement de chiffres (probablement un code-barres)
    if (searchTerm.toLongLong() != 0) {  // Utilisation de toLongLong() pour vérifier un nombre
        queryStr = "SELECT nom, code_barres, type, quantite, date_produit FROM PRODUITS WHERE code_barres LIKE :searchTerm";
    } else {
        queryStr = "SELECT nom, code_barres, type, quantite, date_produit FROM PRODUITS WHERE nom LIKE :searchTerm";
    }

    // Prépare et exécute la requête
    QSqlQuery query;  // Correction de SQUrlQuery en QSqlQuery
    query.prepare(queryStr);
    query.bindValue(":searchTerm", "%" + searchTerm + "%");

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", "Échec de la recherche : " + query.lastError().text());
        return;
    }

    // Nettoie et remplit la table avec les résultats
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    int row = 0;
    while (query.next()) {
        ui->tableWidget->insertRow(row);

        for (int col = 0; col < 5; col++) {
            QTableWidgetItem *item = new QTableWidgetItem();

            if (col == 4) {
                // Formate la date pour la colonne "Date"
                QDate date = query.value(col).toDate();
                item->setText(date.toString("dd/MM/yyyy"));
            } else {
                item->setText(query.value(col).toString());
            }

            item->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(row, col, item);
        }
        row++;
    }

    if (row == 0) {
        QMessageBox::information(this, "Information", "Aucun produit trouvé pour votre recherche.");
    }
}


void MainWindow2::on_triButton_clicked()
{
    // Get the selected sorting criterion from the combo box (TriSelect)
    QString sortBy = ui->TriSelect->currentText();  // "Nom" or "Code Barres"

    // Prepare the SQL query based on the selected sorting criterion
    QString queryStr;
    if (sortBy == "Nom") {
        queryStr = "SELECT nom, code_barres, type, quantite, date_produit FROM PRODUITS ORDER BY nom";
    } else if (sortBy == "Barre Code") {
        queryStr = "SELECT nom, code_barres, type, quantite, date_produit FROM PRODUITS ORDER BY code_barres";
    } else {
        QMessageBox::warning(this, "Erreur", "Critère de tri invalide.");
        return;
    }

    // Execute the query
    QSqlQuery query;  // Correction de QUrlQuery en QSqlQuery
    query.prepare(queryStr);

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", "Échec du tri des produits : " + query.lastError().text());
        return;
    }

    // Clear the table and populate it with sorted results
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    int row = 0;
    while (query.next()) {
        ui->tableWidget->insertRow(row);
        for (int col = 0; col < 5; col++) {
            QTableWidgetItem *item = new QTableWidgetItem();
            if (col == 4) {
                // Format date for the date column
                QDate date = query.value(col).toDate();
                item->setText(date.toString("dd/MM/yyyy"));
            } else {
                item->setText(query.value(col).toString());
            }
            item->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(row, col, item);
        }
        row++;
    }

    if (row == 0) {
        QMessageBox::information(this, "Information", "Aucun produit trouvé pour le critère de tri sélectionné.");
    }
}


// Assurez-vous d'inclure le bon fichier pour `StatWidget`

 // Inclure votre classe pour le graphique

void MainWindow2::on_stat_clicked()
{
    // Create connection instance
    connection c;

    QMap<QString, int> stats;
    // Initialize ranges
    stats["0-10"] = 0;
    stats["11-20"] = 0;
    stats["21-30"] = 0;
    stats["31-40"] = 0;
    stats["41+"] = 0;

    // Create and execute query
    QSqlQuery query;
    if (!query.exec("SELECT QUANTITE FROM PRODUITS")) {
        QMessageBox::critical(this, "Erreur",
                            "Impossible d'exécuter la requête : " + query.lastError().text());
        return;
    }

    // Fill statistics
    while (query.next()) {
        int quantite = query.value(0).toInt();
        if (quantite <= 10) {
            stats["0-10"]++;
        } else if (quantite <= 20) {
            stats["11-20"]++;
        } else if (quantite <= 30) {
            stats["21-30"]++;
        } else if (quantite <= 40) {
            stats["31-40"]++;
        } else {
            stats["41+"]++;
        }
    }

    // Check if there's data
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

    // Create statistics window
    QDialog *statWindow = new QDialog(this);
    statWindow->setWindowTitle("Statistiques des produits");
    statWindow->resize(600, 500);  // Increased height for better visibility

    QVBoxLayout *layout = new QVBoxLayout(statWindow);
    StatWidget2 *statWidget = new StatWidget2(statWindow);
    statWidget->setStatistics(stats);
    layout->addWidget(statWidget);

    // Center the window
    QScreen *screen = QGuiApplication::primaryScreen();
    if (screen) {
        QRect screenGeometry = screen->geometry();
        statWindow->move(
            screenGeometry.center() - statWindow->rect().center()
        );
    }

    statWindow->exec();
    delete statWindow;
}






MainWindow2::~MainWindow2()
{
    // Libérer la mémoire utilisée par l'interface utilisateur
    delete ui;
}


void MainWindow2::on_update_button_clicked()
{
    int oldQuantity = 0;
    // Récupérer la ligne actuellement sélectionnée
    QModelIndexList selectedIndexes = ui->tableWidget->selectionModel()->selectedRows();

    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un produit à modifier.");
        return;
    }

    // Récupérer la première ligne sélectionnée
    int selectedRow = selectedIndexes.first().row();

    // Récupérer le code-barres actuel à partir de la ligne sélectionnée
    QString currentCodeBarres = ui->tableWidget->item(selectedRow, 1)->text();

    // Récupérer les valeurs saisies
    QString nom = ui->lineEdit_nom->text();
    QString code_barres = ui->lineEdit_code->text();
    QString type = ui->lineEdit_type->text();
    int quantite = ui->lineEdit_quantite->value(); // QSpinBox
    QString date_produit = ui->lineEdit_date->date().toString("yyyy-MM-dd"); // QDateEdit

    // Valider les champs vides
    if (nom.isEmpty() || code_barres.isEmpty() || type.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Tous les champs doivent être remplis !");
        return;
    }

    // Valider la quantité
    if (quantite <= 0) {
        QMessageBox::warning(this, "Erreur", "La quantité doit être supérieure à 0 !");
        return;
    }

    // Vérifier si le nouveau code-barres existe déjà
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM PRODUITS WHERE code_barres = :new_code_barres AND code_barres <> :current_code_barres");
    checkQuery.bindValue(":new_code_barres", code_barres);
    checkQuery.bindValue(":current_code_barres", currentCodeBarres);

    if (!checkQuery.exec()) {
        qDebug() << "Erreur lors de la vérification du code-barres :" << checkQuery.lastError().text();
        QMessageBox::critical(this, "Erreur", "Erreur lors de la vérification du code-barres.");
        return;
    }

    if (checkQuery.next() && checkQuery.value(0).toInt() > 0) {
        QMessageBox::warning(this, "Erreur", "Ce code-barres existe déjà !");
        return;
    }

    // Prepare the query to get the quantity of the product from the database
        QSqlQuery query1;
        query1.prepare("SELECT quantite FROM PRODUITS WHERE nom = :nom");
        query1.bindValue(":nom",nom );

        // Execute the query
        if (query1.exec()) {
            // If the query executed successfully, fetch the result
            if (query1.next()) {
                oldQuantity = query1.value(0).toInt(); // Retrieve the quantity value
            } else {
                qDebug() << "Product not found in database.";
            }
        } else {
            qDebug() << "Query failed: " << query1.lastError();
        }

    // Préparer la requête de mise à jour
    QSqlQuery query;
    query.prepare("UPDATE PRODUITS SET "
                  "nom = :nom, "
                  "code_barres = :new_code_barres, "
                  "type = :type, "
                  "quantite = :quantite, "
                  "date_produit = TO_DATE(:date_produit, 'YYYY-MM-DD') "
                  "WHERE code_barres = :current_code_barres");

    query.bindValue(":nom", nom);
    query.bindValue(":new_code_barres", code_barres);
    query.bindValue(":type", type);
    query.bindValue(":quantite", quantite);
    query.bindValue(":date_produit", date_produit);
    query.bindValue(":current_code_barres", currentCodeBarres);

    if (query.exec()) {
        if (query.numRowsAffected() > 0) {
            QMessageBox::information(this, "Succès", "Produit modifié avec succès !");
            // Réinitialiser les champs
            ui->lineEdit_nom->clear();
            ui->lineEdit_code->clear();
            ui->lineEdit_type->clear();
            ui->lineEdit_quantite->setValue(1);
            ui->lineEdit_date->setDate(QDate::currentDate());

            // Rafraîchir la table
            afficherProduits();
        } else {
            QMessageBox::warning(this, "Erreur", "Aucun produit trouvé avec ce code-barres.");
        }
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification du produit : " + query.lastError().text());
    }
    HistoryManager::recordChange(nom,"modified",oldQuantity, quantite);
}
void MainWindow2::on_tableWidget_cellClicked(int row)
{
    // Vérifier que la ligne est valide
    if (row < 0 || row >= ui->tableWidget->rowCount()) {
        QMessageBox::warning(this, "Erreur", "Ligne invalide sélectionnée !");
        return;
    }

    // Récupérer les données de la ligne
    QString nom = ui->tableWidget->item(row, 0)->text();
    QString code_barres = ui->tableWidget->item(row, 1)->text();
    QString type = ui->tableWidget->item(row, 2)->text();
    QString quantite = ui->tableWidget->item(row, 3)->text();
    QString date_str = ui->tableWidget->item(row, 4)->text();

    // Remplir les champs
    ui->lineEdit_nom->setText(nom);
    ui->lineEdit_code->setText(code_barres);
    ui->lineEdit_type->setText(type);
    ui->lineEdit_quantite->setValue(quantite.toInt());

    // Tentative de conversion de la date
    QDate date = QDate::fromString(date_str, "yyyy-MM-dd");
    if (!date.isValid()) {
        // Si le format "yyyy-MM-dd" échoue, essayons "dd/MM/yyyy"
        date = QDate::fromString(date_str, "dd/MM/yyyy");
    }
    if (!date.isValid()) {
        QMessageBox::warning(this, "Erreur", "Format de date invalide pour la ligne sélectionnée : " + date_str);
        return;
    }

    // Appliquer la date au champ de saisie
    ui->lineEdit_date->setDate(date);
}

// Créer un dossier (par exemple "data") dans le répertoire du projet
void MainWindow2::createDirectory()
{
    QDir dir;
    QString path = "data";  // Le nom du dossier que tu veux créer

    // Vérifier si le dossier existe déjà
    if (!dir.exists(path)) {
        // Créer le dossier
        if (dir.mkpath(path)) {
            QMessageBox::information(this, "Succès", "Le dossier a été créé avec succès.");
        } else {
            QMessageBox::critical(this, "Erreur", "Impossible de créer le dossier.");
        }
    } else {
        QMessageBox::information(this, "Info", "Le dossier existe déjà.");
    }
}



void MainWindow2::viewHistory()
{
    QString dirPath = "";  // Dossier relatif
    QString filePath = "C:/Users/Tayma Store/Desktop/integration/history.txt";  // Fichier d'historique

    // Afficher le répertoire courant et le chemin complet du fichier
    qDebug() << "Répertoire courant : " << QDir::currentPath();
    qDebug() << "Chemin complet du fichier : " << filePath;
/*
    // Vérifier si le dossier existe
    QDir dir;
    if (!dir.exists(dirPath)) {
        if (!dir.mkpath(dirPath)) {
            QMessageBox::critical(this, "Erreur", "Impossible de créer le dossier 'historique'.");
            return;
        }
    }
*/
    // Vérifier si le fichier existe
    if (!QFile::exists(filePath)) {
        QMessageBox::critical(this, "Erreur", "Le fichier d'historique n'existe pas.");
        return;
    }

    // Ouvrir le fichier pour lecture
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir le fichier d'historique. Vérifie le chemin.");
        return;
    }

    // Lire le contenu du fichier
    QTextStream in(&file);
    QString historyContent = in.readAll();

    // Afficher le contenu dans le QTextEdit
    ui->textEditHistory->setText(historyContent);

    // Fermer le fichier
    file.close();
}


void MainWindow2::on_pushButton_2_clicked()
{
    window = new MainWindow(this); // Crée une nouvelle instance si elle n'existe pas

    window->show();

// Optionnel : masquer la fenêtre actuelle
this->hide();
}


void MainWindow2::on_pushButton_3_clicked()
{
    window3 = new MainWindow3(this); // Crée une nouvelle instance si elle n'existe pas

    window3->show();

// Optionnel : masquer la fenêtre actuelle
this->hide();

}
