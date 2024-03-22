#include "database.h"


SQLiteManager::SQLiteManager(const QString &path, int limit) {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);
    this->limit = limit;
    if (!db.open()) {
        qDebug() << "Error: connection with database fail";
    } else {
        qDebug() << "Database: connection ok";
        createTable();
    }
}

SQLiteManager::~SQLiteManager()
{
    if(db.isOpen())
        db.close();
}

void SQLiteManager::createTable() {
    QSqlQuery query;
    query.prepare("CREATE TABLE IF NOT EXISTS tr (key TEXT PRIMARY KEY, value "
                  "TEXT, edittime INTEGER)");
    if (!query.exec())
        qDebug() << query.executedQuery() << " failed!";
}

void SQLiteManager::putValue(const QString &key, const QString &value) {
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM tr");
    if(!checkQuery.exec())
        qDebug() << checkQuery.executedQuery() << " failed!";

    if (checkQuery.next() && checkQuery.value(0).toInt() > limit) {
        QSqlQuery deleteQuery;
        deleteQuery.prepare("DELETE FROM tr WHERE edittime = (SELECT MIN(edittime) FROM tr)");
        if(!deleteQuery.exec())
            qDebug() << deleteQuery.executedQuery() << " failed!";        }

    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT OR REPLACE INTO tr VALUES (?, ?, ?)");
    insertQuery.addBindValue(key);
    insertQuery.addBindValue(value);
    insertQuery.addBindValue(QDateTime::currentSecsSinceEpoch()); // current Unix timestamp
    if(!insertQuery.exec())
        qDebug() << insertQuery.executedQuery() << " failed!";

    // qDebug() << "insertQuery: " << insertQuery.executedQuery() << "in: " << db.connectionNames();
}

QString SQLiteManager::getValue(const QString &key) {
    QSqlQuery query;
    query.prepare("SELECT value FROM tr WHERE key = ?");
    query.addBindValue(key);
    if(!query.exec())
        qDebug() << query.executedQuery() << " failed!";

    if (query.next()) {
        return query.value(0).toString();
    }

    return "";
}
