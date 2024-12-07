#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include "ProductHistory.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    void addProductHistory(int productId, ProductHistory::Action action, const QString& details);
    QVector<ProductHistory> getProductHistory(int productId);

private:
    Ui::MainWindow* ui;
    QVector<ProductHistory> m_productHistory;
};

#endif // MAINWINDOW_H
