#include "mainwindow.h"
#include "ui_mainwindow.h"
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


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupTable();
    afficherProduits();

        }

void MainWindow::setupTable() {
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

void MainWindow::on_on_btnAjouterProduit_clicked_clicked()
{
    QString nom = ui->lineEdit_nom->text();
    QString code_barres = ui->lineEdit_code->text();
    QString type = ui->lineEdit_type->text();
    int quantite = ui->lineEdit_quantite->value();
    QString date_produit = ui->lineEdit_date->date().toString("yyyy-MM-dd");

    // Validate empty fields
    if (nom.isEmpty() || code_barres.isEmpty() || type.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Tous les champs doivent être remplis !");
        return;
    }

    // Check if code_barres already exists
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM produits WHERE code_barres = :code_barres");
    checkQuery.bindValue(":code_barres", code_barres);

    if (checkQuery.exec() && checkQuery.next()) {
        if (checkQuery.value(0).toInt() > 0) {
            QMessageBox::warning(this, "Erreur", "Ce code-barres existe déjà !");
            return;
        }
    }

    Produit nouveauProduit(nom, code_barres, type, quantite, date_produit);

    if (nouveauProduit.ajouter()) {
        QMessageBox::information(this, "Succès", "Produit ajouté avec succès !");
        // Clear fields
        ui->lineEdit_nom->clear();
        ui->lineEdit_code->clear();
        ui->lineEdit_type->clear();
        ui->lineEdit_quantite->setValue(1);
        ui->lineEdit_date->setDate(QDate::currentDate());

        // Refresh the table
        afficherProduits();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout du produit.");
    }
}

void MainWindow::afficherProduits() {
    qDebug() << "Starting afficherProduits()";

    QSqlQuery query;
    query.prepare("SELECT nom, code_barres, type, quantite, date_produit FROM produits ORDER BY nom");

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

void MainWindow::on_pushButton_clicked() {
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

void MainWindow::on_exportButton_clicked()
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
    query.prepare("SELECT nom, code_barres, type, quantite, date_produit FROM produits ORDER BY nom");

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

void MainWindow::on_buyButton_clicked()
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
    query.prepare("SELECT nom, quantite FROM produits WHERE code_barres = :barcode");
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
        updateQuery.prepare("UPDATE produits SET quantite = quantite - :requestedQuantity WHERE code_barres = :barcode");
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


void MainWindow::on_searchButton_clicked()
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
        queryStr = "SELECT nom, code_barres, type, quantite, date_produit FROM produits WHERE code_barres LIKE :searchTerm";
    } else {
        queryStr = "SELECT nom, code_barres, type, quantite, date_produit FROM produits WHERE nom LIKE :searchTerm";
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


void MainWindow::on_triButton_clicked()
{
    // Get the selected sorting criterion from the combo box (TriSelect)
    QString sortBy = ui->TriSelect->currentText();  // "Nom" or "Code Barres"

    // Prepare the SQL query based on the selected sorting criterion
    QString queryStr;
    if (sortBy == "Nom") {
        queryStr = "SELECT nom, code_barres, type, quantite, date_produit FROM produits ORDER BY nom";
    } else if (sortBy == "Barre Code") {
        queryStr = "SELECT nom, code_barres, type, quantite, date_produit FROM produits ORDER BY code_barres";
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


MainWindow::~MainWindow()
{
    // Libérer la mémoire utilisée par l'interface utilisateur
    delete ui;
}


