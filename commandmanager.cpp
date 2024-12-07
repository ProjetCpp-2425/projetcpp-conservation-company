#include "commandmanager.h"
#include "ui_mainwindow.h"  // Include the generated UI header for MainWindow

CommandManager::CommandManager(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::MainWindow)  // Initialize the UI object for MainWindow
{
    ui->setupUi(this);  // Set up the UI for the MainWindow

    // Connect the button signal to the appropriate slot
    connect(ui->actionShowCommands, &QPushButton::clicked, this, &CommandManager::loadCommands);
}

CommandManager::~CommandManager()
{
    delete ui;  // Clean up the UI object
}

void CommandManager::loadCommands()
{
    ui->tableView->resizeColumnsToContents();  // Example usage of the UI elements
    // Your logic to load commands
}
