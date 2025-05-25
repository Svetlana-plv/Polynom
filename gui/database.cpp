#include "database.h"


bool DatabaseManager::initDatabase() {
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(path);
    QString dbPath = path + "/polynoms.db";

    qDebug() << dbPath;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        qDebug() << "error connect database:" << db.lastError().text();
        return false;
    }

    QSqlQuery query;

    if (!query.exec(
        "CREATE TABLE IF NOT EXISTS profiles ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL, "
        "state INTEGER NOT NULL)"
    )) {
        qDebug() << "error to create profiles:" << query.lastError().text();
        return false;
    }

    if (!query.exec(
        "CREATE TABLE IF NOT EXISTS polynomials ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "profile_id INTEGER NOT NULL, "
        "key TEXT, "
        "value TEXT, "
        "FOREIGN KEY(profile_id) REFERENCES profiles(id) ON DELETE CASCADE)"
    )) {
        qDebug() << "Ошибка создания таблицы polynomials:" << query.lastError().text();
        return false;
    }

    return true;
}

QSqlDatabase& DatabaseManager::database() {
    static QSqlDatabase db = QSqlDatabase::database();
    return db;
}