#include "PreferencesDialog.h"
#include <QComboBox>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QTranslator>
#include <QVBoxLayout>
#include <QApplication>
#include <QMessageBox>
#include <QDebug>  // Include for debugging output
#include <QSettings>

PreferencesDialog::PreferencesDialog(QWidget *parent) : QDialog(parent) {
    setupUI();  // Initialize the UI
    loadSettings();  // Load saved preferences (if they exist)
}

PreferencesDialog::~PreferencesDialog() {
    // Clean up resources if needed
}

void PreferencesDialog::setupUI() {
    // Create combo box for selecting language
    comboBoxLanguage = new QComboBox(this);
    comboBoxLanguage->addItem("Français", "fr");
    comboBoxLanguage->addItem("English", "en");
    comboBoxLanguage->addItem("Arabic", "ar");
    comboBoxLanguage->addItem("Russian", "ru");
    comboBoxLanguage->addItem("Spanish", "es");
    comboBoxLanguage->addItem("German", "de");
    comboBoxLanguage->addItem("Mandarin Chinese", "zh");
    comboBoxLanguage->addItem("Bengali", "bn");
    comboBoxLanguage->addItem("Hindi", "hi");

    // Create button box with OK and Cancel buttons
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &PreferencesDialog::onOkClicked);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &PreferencesDialog::onCancelClicked);

    // Layout setup
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(comboBoxLanguage);
    layout->addWidget(buttonBox);
}

void PreferencesDialog::loadSettings() {
    // Load the saved language preference
    QSettings settings("config.ini", QSettings::IniFormat);
    comboBoxLanguage->setCurrentText(settings.value("language", "fr").toString());
}

void PreferencesDialog::onOkClicked() {
    applyChanges();  // Apply changes (save language and load translator)
    accept();  // Close the dialog
}

void PreferencesDialog::onCancelClicked() {
    reject();  // Close the dialog without applying changes
}

void PreferencesDialog::applyChanges() {
    // Save the selected language
    QString selectedLanguage = comboBoxLanguage->currentData().toString();
    QSettings settings("config.ini", QSettings::IniFormat);
    settings.setValue("language", selectedLanguage);  // Save selected language to settings file

    // Construct the path to the .qm file
    QString filePath = QString("translations/app_%1.qm").arg(selectedLanguage);

    // Debug: Print the file path to check
    qDebug() << "Attempting to load translation file:" << filePath;

    // Load the translation file
    QTranslator *translator = new QTranslator(this);
    if (translator->load(filePath)) {
        qApp->installTranslator(translator);
        qDebug() << "Translation loaded successfully!";
    } else {
        qDebug() << "Failed to load translation file at:" << filePath;
        QMessageBox::warning(this, tr("Erreur de traduction"), tr("Impossible de charger le fichier de traduction."));
    }
}
