#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H

#include <QString>
#include <QDateTime>
#include <QFile>
#include <QTextStream>

class HistoryManager {
public:
    static void recordChange(const QString& productName, const QString& changeType,
                             int oldQuantity, int newQuantity);
    static void showHistory();  // Affiche l'historique des changements dans QTextEdit
};

#endif // HISTORYMANAGER_H
