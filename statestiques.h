#ifndef STATESTIQUES_H
#define STATESTIQUES_H

#include <QWidget>
#include <QMap>

class StatWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StatWidget(QWidget *parent = nullptr);
    void setStatistics(const QMap<QString, int> &stats);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QMap<QString, int> statistics;
};

#endif
