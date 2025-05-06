#pragma once

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>



class DatabaseManager {
public:
    static bool initDatabase();
    static QSqlDatabase& database();
};