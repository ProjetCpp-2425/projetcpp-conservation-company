/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QLabel *label;
    QLabel *label_2;
    QWidget *widget_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *widget_5;
    QWidget *widget_4;
    QWidget *widget_6;
    QLabel *label_9;
    QLabel *label_10;
    QLineEdit *lineEdit_nom;
    QLabel *label_11;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_16;
    QLineEdit *lineEdit_email;
    QLineEdit *lineEdit_telephone;
    QLineEdit *lineEdit_identifiant;
    QLineEdit *lineEdit_prenom;
    QPushButton *pushButton_ajouter;
    QDateTimeEdit *dateTimeEdit;
    QLineEdit *lineEdit_rechercher;
    QLabel *label_19;
    QLineEdit *lineEdit_supprimer;
    QLabel *label_17;
    QLineEdit *lineEdit_tri;
    QLineEdit *lineEdit_enregistrer;
    QTableView *tableView;
    QPushButton *pushButton_enregistrer;
    QPushButton *pushButton_supprimer;
    QPushButton *pushButton_trier;
    QPushButton *pushButton_rechercher;
    QPushButton *pushButton_modifier;
    QLineEdit *lineEdit_modifier;
    QPushButton *pushButton_calculerScore;
    QLineEdit *lineEdit_score;
    QWidget *tab_2;
    QWidget *widget_8;
    QLabel *label_23;
    QFrame *line;
    QLabel *label_24;
    QPushButton *pushButton_statistiques;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1331, 669);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(-10, 10, 221, 651));
        widget->setStyleSheet(QString::fromUtf8("background-color: rgb(51, 153, 119);"));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 50, 131, 31));
        label->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 140, 131, 31));
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        widget_2 = new QWidget(widget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setGeometry(QRect(0, 220, 221, 71));
        widget_2->setStyleSheet(QString::fromUtf8("background-color: rgb(104, 209, 155);"));
        label_3 = new QLabel(widget_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 10, 161, 41));
        label_3->setStyleSheet(QString::fromUtf8("color: rgb(0, 134, 98);"));
        label_4 = new QLabel(widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(30, 350, 131, 31));
        label_4->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_5 = new QLabel(widget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(30, 420, 131, 31));
        label_5->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(210, 0, 1091, 651));
        tabWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        widget_5 = new QWidget(tab);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        widget_5->setGeometry(QRect(-10, -40, 1121, 641));
        widget_5->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"background-color: rgb(237, 255, 239);"));
        widget_4 = new QWidget(widget_5);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        widget_4->setGeometry(QRect(10, 20, 271, 611));
        widget_4->setStyleSheet(QString::fromUtf8("background-color: rgb(177, 216, 183);\n"
"background-color: rgb(188, 229, 203);"));
        widget_6 = new QWidget(widget_4);
        widget_6->setObjectName(QString::fromUtf8("widget_6"));
        widget_6->setGeometry(QRect(0, 0, 211, 61));
        widget_6->setStyleSheet(QString::fromUtf8("background-color: rgb(48, 173, 138);\n"
"background-color: rgb(31, 208, 193);"));
        label_9 = new QLabel(widget_6);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(12, 20, 191, 20));
        label_9->setStyleSheet(QString::fromUtf8("\n"
"font: 700 11pt \"Segoe UI\";\n"
"\n"
"color: rgb(26, 202, 167);\n"
"color: rgb(21, 21, 21);\n"
""));
        label_10 = new QLabel(widget_4);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(10, 480, 181, 20));
        label_10->setStyleSheet(QString::fromUtf8("font: 700 9pt \"Segoe UI\";\n"
"font: 700 12pt \"Segoe UI\";\n"
""));
        lineEdit_nom = new QLineEdit(widget_4);
        lineEdit_nom->setObjectName(QString::fromUtf8("lineEdit_nom"));
        lineEdit_nom->setGeometry(QRect(20, 120, 161, 26));
        lineEdit_nom->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_11 = new QLabel(widget_4);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(10, 80, 181, 20));
        label_11->setStyleSheet(QString::fromUtf8("font: 700 9pt \"Segoe UI\";\n"
"font: 700 12pt \"Segoe UI\";\n"
""));
        label_13 = new QLabel(widget_4);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(10, 400, 181, 20));
        label_13->setStyleSheet(QString::fromUtf8("font: 700 9pt \"Segoe UI\";\n"
"font: 700 12pt \"Segoe UI\";\n"
""));
        label_14 = new QLabel(widget_4);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(10, 340, 181, 20));
        label_14->setStyleSheet(QString::fromUtf8("font: 700 9pt \"Segoe UI\";\n"
"font: 700 12pt \"Segoe UI\";\n"
""));
        label_15 = new QLabel(widget_4);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(10, 250, 181, 20));
        label_15->setStyleSheet(QString::fromUtf8("font: 700 9pt \"Segoe UI\";\n"
"font: 700 12pt \"Segoe UI\";\n"
""));
        label_16 = new QLabel(widget_4);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(10, 170, 181, 20));
        label_16->setStyleSheet(QString::fromUtf8("font: 700 9pt \"Segoe UI\";\n"
"font: 700 12pt \"Segoe UI\";\n"
""));
        lineEdit_email = new QLineEdit(widget_4);
        lineEdit_email->setObjectName(QString::fromUtf8("lineEdit_email"));
        lineEdit_email->setGeometry(QRect(20, 440, 161, 26));
        lineEdit_email->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        lineEdit_telephone = new QLineEdit(widget_4);
        lineEdit_telephone->setObjectName(QString::fromUtf8("lineEdit_telephone"));
        lineEdit_telephone->setGeometry(QRect(20, 370, 161, 26));
        lineEdit_telephone->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        lineEdit_identifiant = new QLineEdit(widget_4);
        lineEdit_identifiant->setObjectName(QString::fromUtf8("lineEdit_identifiant"));
        lineEdit_identifiant->setGeometry(QRect(20, 290, 161, 26));
        lineEdit_identifiant->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        lineEdit_prenom = new QLineEdit(widget_4);
        lineEdit_prenom->setObjectName(QString::fromUtf8("lineEdit_prenom"));
        lineEdit_prenom->setGeometry(QRect(20, 210, 161, 26));
        lineEdit_prenom->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pushButton_ajouter = new QPushButton(widget_4);
        pushButton_ajouter->setObjectName(QString::fromUtf8("pushButton_ajouter"));
        pushButton_ajouter->setGeometry(QRect(70, 560, 93, 29));
        dateTimeEdit = new QDateTimeEdit(widget_4);
        dateTimeEdit->setObjectName(QString::fromUtf8("dateTimeEdit"));
        dateTimeEdit->setGeometry(QRect(30, 510, 194, 26));
        dateTimeEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        lineEdit_rechercher = new QLineEdit(widget_5);
        lineEdit_rechercher->setObjectName(QString::fromUtf8("lineEdit_rechercher"));
        lineEdit_rechercher->setGeometry(QRect(420, 150, 161, 26));
        lineEdit_rechercher->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(216, 216, 216);"));
        label_19 = new QLabel(widget_5);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(530, 540, 63, 41));
        label_19->setPixmap(QPixmap(QString::fromUtf8("../Downloads/Screenshot_2024-10-05_225400-removebg-preview.png")));
        label_19->setScaledContents(true);
        lineEdit_supprimer = new QLineEdit(widget_5);
        lineEdit_supprimer->setObjectName(QString::fromUtf8("lineEdit_supprimer"));
        lineEdit_supprimer->setGeometry(QRect(770, 550, 161, 26));
        lineEdit_supprimer->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(216, 216, 216);"));
        label_17 = new QLabel(widget_5);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(280, 20, 771, 91));
        label_17->setPixmap(QPixmap(QString::fromUtf8("../OneDrive - ESPRIT/Pictures/Screenshots/Screenshot 2024-10-06 205302.png")));
        label_17->setScaledContents(true);
        lineEdit_tri = new QLineEdit(widget_5);
        lineEdit_tri->setObjectName(QString::fromUtf8("lineEdit_tri"));
        lineEdit_tri->setGeometry(QRect(880, 150, 161, 26));
        lineEdit_tri->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(216, 216, 216);"));
        lineEdit_enregistrer = new QLineEdit(widget_5);
        lineEdit_enregistrer->setObjectName(QString::fromUtf8("lineEdit_enregistrer"));
        lineEdit_enregistrer->setGeometry(QRect(410, 550, 131, 26));
        lineEdit_enregistrer->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(216, 216, 216);"));
        tableView = new QTableView(widget_5);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(300, 240, 761, 271));
        tableView->setStyleSheet(QString::fromUtf8("background-color: rgb(188,229,203);"));
        pushButton_enregistrer = new QPushButton(widget_5);
        pushButton_enregistrer->setObjectName(QString::fromUtf8("pushButton_enregistrer"));
        pushButton_enregistrer->setGeometry(QRect(290, 550, 111, 31));
        pushButton_enregistrer->setStyleSheet(QString::fromUtf8("font: 700 12pt \"Segoe UI\";\n"
""));
        pushButton_supprimer = new QPushButton(widget_5);
        pushButton_supprimer->setObjectName(QString::fromUtf8("pushButton_supprimer"));
        pushButton_supprimer->setGeometry(QRect(640, 550, 111, 31));
        pushButton_supprimer->setStyleSheet(QString::fromUtf8("font: 700 12pt \"Segoe UI\";\n"
""));
        pushButton_trier = new QPushButton(widget_5);
        pushButton_trier->setObjectName(QString::fromUtf8("pushButton_trier"));
        pushButton_trier->setGeometry(QRect(740, 150, 111, 31));
        pushButton_trier->setStyleSheet(QString::fromUtf8("font: 700 12pt \"Segoe UI\";\n"
""));
        pushButton_rechercher = new QPushButton(widget_5);
        pushButton_rechercher->setObjectName(QString::fromUtf8("pushButton_rechercher"));
        pushButton_rechercher->setGeometry(QRect(290, 150, 111, 31));
        pushButton_rechercher->setStyleSheet(QString::fromUtf8("font: 700 12pt \"Segoe UI\";\n"
""));
        pushButton_modifier = new QPushButton(widget_5);
        pushButton_modifier->setObjectName(QString::fromUtf8("pushButton_modifier"));
        pushButton_modifier->setGeometry(QRect(750, 200, 111, 31));
        pushButton_modifier->setStyleSheet(QString::fromUtf8("font: 700 12pt \"Segoe UI\";\n"
""));
        lineEdit_modifier = new QLineEdit(widget_5);
        lineEdit_modifier->setObjectName(QString::fromUtf8("lineEdit_modifier"));
        lineEdit_modifier->setGeometry(QRect(880, 200, 161, 26));
        lineEdit_modifier->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(216, 216, 216);"));
        pushButton_calculerScore = new QPushButton(widget_5);
        pushButton_calculerScore->setObjectName(QString::fromUtf8("pushButton_calculerScore"));
        pushButton_calculerScore->setGeometry(QRect(300, 190, 111, 31));
        pushButton_calculerScore->setStyleSheet(QString::fromUtf8("font: 700 12pt \"Segoe UI\";\n"
""));
        lineEdit_score = new QLineEdit(widget_5);
        lineEdit_score->setObjectName(QString::fromUtf8("lineEdit_score"));
        lineEdit_score->setGeometry(QRect(420, 190, 161, 26));
        lineEdit_score->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(216, 216, 216);"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        widget_8 = new QWidget(tab_2);
        widget_8->setObjectName(QString::fromUtf8("widget_8"));
        widget_8->setGeometry(QRect(0, 0, 1111, 721));
        widget_8->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"background-color: rgb(237, 255, 239);"));
        label_23 = new QLabel(widget_8);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setGeometry(QRect(50, 180, 121, 20));
        label_23->setStyleSheet(QString::fromUtf8("font: 700 12pt \"Segoe UI\";"));
        line = new QFrame(widget_8);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(540, 200, 20, 291));
        line->setStyleSheet(QString::fromUtf8("font: 700 10pt \"Segoe UI\";"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        label_24 = new QLabel(widget_8);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setGeometry(QRect(20, -20, 1051, 141));
        label_24->setPixmap(QPixmap(QString::fromUtf8("../OneDrive - ESPRIT/Pictures/Screenshots/Screenshot 2024-10-06 204147.png")));
        label_24->setScaledContents(true);
        pushButton_statistiques = new QPushButton(widget_8);
        pushButton_statistiques->setObjectName(QString::fromUtf8("pushButton_statistiques"));
        pushButton_statistiques->setGeometry(QRect(330, 190, 93, 29));
        tabWidget->addTab(tab_2, QString());
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1331, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:14pt;\">        Employ\303\251</span></p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:14pt;\">Clients</span></p></body></html>", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:14pt;\">Fourniseurs</span></p></body></html>", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:14pt;\">Equipemnts</span></p></body></html>", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:14pt;\">Produits</span></p></body></html>", nullptr));
#if QT_CONFIG(whatsthis)
        tabWidget->setWhatsThis(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Fonctionalites</p></body></html>", nullptr));
#endif // QT_CONFIG(whatsthis)
        label_9->setText(QCoreApplication::translate("MainWindow", "Ajouter un fourniseur", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "DATETIMEF", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "NOMF", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "EMAILF", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "TELEPHONEF", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "IDENTIFIANTF", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "PRENOMF", nullptr));
        pushButton_ajouter->setText(QCoreApplication::translate("MainWindow", "ajouter", nullptr));
        lineEdit_rechercher->setText(QCoreApplication::translate("MainWindow", "identifiant", nullptr));
        label_19->setText(QString());
        lineEdit_supprimer->setText(QCoreApplication::translate("MainWindow", "identifiant", nullptr));
        label_17->setText(QString());
        lineEdit_tri->setText(QCoreApplication::translate("MainWindow", "date et time", nullptr));
        lineEdit_enregistrer->setText(QCoreApplication::translate("MainWindow", "exel", nullptr));
        pushButton_enregistrer->setText(QCoreApplication::translate("MainWindow", "enregistrer", nullptr));
        pushButton_supprimer->setText(QCoreApplication::translate("MainWindow", "supprimer", nullptr));
        pushButton_trier->setText(QCoreApplication::translate("MainWindow", "tri", nullptr));
        pushButton_rechercher->setText(QCoreApplication::translate("MainWindow", "rechercher", nullptr));
        pushButton_modifier->setText(QCoreApplication::translate("MainWindow", "modifier", nullptr));
        lineEdit_modifier->setText(QCoreApplication::translate("MainWindow", "identifiant", nullptr));
        pushButton_calculerScore->setText(QCoreApplication::translate("MainWindow", "Score", nullptr));
        lineEdit_score->setText(QCoreApplication::translate("MainWindow", "identifiant", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "Tab 1", nullptr));
        label_23->setText(QCoreApplication::translate("MainWindow", "Statistiques", nullptr));
        label_24->setText(QString());
        pushButton_statistiques->setText(QCoreApplication::translate("MainWindow", "Show stat", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Tab 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
