#ifndef STATWIDGET_H
#define STATWIDGET_H
#include <QWidget>
#include <QMap>
#include <QPainter>

class StatWidget : public QWidget {
    Q_OBJECT

public:
    explicit StatWidget(QWidget *parent = nullptr);
    void setStatistics(const QMap<QString, int> &stats); // Définit les données pour le diagramme

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QMap<QString, int> statistics; // Contient les données pour le graphique
};

#endif // STATWIDGET_H

