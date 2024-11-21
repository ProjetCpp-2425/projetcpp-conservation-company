#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QUrlQuery>
#include <QSqlDatabase>
#include <QPushButton>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setupTable();
    void afficherProduits();

private slots:
    void on_on_btnAjouterProduit_clicked_clicked();

    void on_pushButton_clicked(); // Slot for delete functionality

    void on_exportButton_clicked();

    void on_buyButton_clicked();

    void on_searchButton_clicked();

    void on_triButton_clicked();

    void on_stat_clicked();


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

