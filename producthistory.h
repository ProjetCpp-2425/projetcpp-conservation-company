#ifndef PRODUCTHISTORY_H
#define PRODUCTHISTORY_H

#include <QString>
#include <QDateTime>

class ProductHistory {
public:
    enum class Action { Added, Updated, Deleted };

    ProductHistory(const QString& barcode, Action action, const QString& details, const QDateTime& timestamp)
        : m_barcode(barcode), m_action(action), m_details(details), m_timestamp(timestamp) {}

    QString barcode() const { return m_barcode; }
    Action action() const { return m_action; }
    QString details() const { return m_details; }
    QDateTime timestamp() const { return m_timestamp; }

private:
    QString m_barcode;  // Utilisation d'un code à barres comme identifiant unique
    Action m_action;
    QString m_details;
    QDateTime m_timestamp;
};

#endif // PRODUCTHISTORY_H
