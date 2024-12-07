#ifndef PREFERENCESDIALOG_H
#define PREFERENCESDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QTranslator>
#include <QSettings>
#include <QMessageBox>

class PreferencesDialog : public QDialog {
    Q_OBJECT

public:
    explicit PreferencesDialog(QWidget *parent = nullptr);
    ~PreferencesDialog(); // Destructor

private slots:
    void onOkClicked();    // Slot for the "OK" button
    void onCancelClicked(); // Slot for the "Cancel" button

private:
    void setupUI();         // Setup the UI elements
    void loadSettings();    // Load saved settings (language)
    void applyChanges();    // Apply changes (save language, load translator)

    QComboBox *comboBoxLanguage;  // ComboBox for selecting language
    QDialogButtonBox *buttonBox;  // Dialog button box (OK & Cancel)
};

#endif // PREFERENCESDIALOG_H
