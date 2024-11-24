#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>

class Connection
{
private:
    QSqlDatabase db;

public:
    Connection();
    bool createconnection();
    void closeConnection();
    QSqlDatabase getDatabase() { return db; }  // Added getter for database access
};

#endif
