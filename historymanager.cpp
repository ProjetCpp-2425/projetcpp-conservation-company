#include "historymanager.h"
#include <QFileDialog>
#include <QTextEdit>
#include <QMessageBox>

void HistoryManager::recordChange(const QString& productName, const QString& changeType,
                                  int oldQuantity, int newQuantity) {
    QFile file("C:/Users/Tayma Store/Desktop/integration/history.txt"); // Le fichier où l'historique sera sauvegardé

    // Vérification du chemin
    qDebug() << "File path: " << file.fileName();

    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Erreur", "Impossible d'ouvrir le fichier d'historique.");
        return;
    } else {
        qDebug() << "File opened successfully.";
    }

    QTextStream out(&file);

    // Log what will be written to the file
    qDebug() << "Writing to file: "
             << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") << " | "
             << changeType << " | "
             << productName << " | "
             << "Avant: " << oldQuantity << " | "
             << "Après: " << newQuantity;

    out << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") << " | "
        << changeType << " | "
        << productName << " | "
        << "Avant: " << oldQuantity << " | "
        << "Après: " << newQuantity << "\n";

    // Optionally flush the stream
    out.flush();

    file.close();
}


/*
void HistoryManager::recordChange(const QString& productName, const QString& changeType,
                                  int oldQuantity, int newQuantity) {
    QFile file("C:/Users/samaa/OneDrive/Bureau/produits/history.txt"); // Le fichier où l'historique sera sauvegardé
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Erreur", "Impossible d'ouvrir le fichier d'historique.");
        return;
    } else {
        qDebug() << "File opened successfully.";
    }
    QTextStream out(&file);

    qDebug() << "Writing to file: "
             << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") << " | "
             << changeType << " | "
             << productName << " | "
             << "Avant: " << oldQuantity << " | "
             << "Après: " << newQuantity;

    out << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") << " | "
        << changeType << " | "
        << productName << " | "
        << "Avant: " << oldQuantity << " | "
        << "Après: " << newQuantity << "\n";
    file.close();
}
*/
void HistoryManager::showHistory() {
    QFile file("history.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Erreur", "Impossible d'ouvrir le fichier d'historique.");
        return;
    }

    QTextStream in(&file);
    QString content = in.readAll();
    file.close();

    // Afficher dans un QTextEdit (par exemple dans la fenêtre principale)
    QTextEdit* historyView = new QTextEdit();
    historyView->setPlainText(content);
    historyView->setWindowTitle("Historique des Modifications");
    historyView->show();
}
