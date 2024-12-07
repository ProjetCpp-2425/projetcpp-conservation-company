#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include <QWidget>
#include <QSqlTableModel>

namespace Ui {
class CommandManager;
}

class CommandManager : public QWidget
{
    Q_OBJECT

public:
    explicit CommandManager(QWidget *parent = nullptr);
    ~CommandManager();
    void loadCommands(); // Mettez cette ligne en public

private slots:


private:
    Ui::CommandManager *ui;
    QSqlTableModel *model;
};

#endif // COMMANDMANAGER_H
