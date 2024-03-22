#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QtSql>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDateTime>

class SQLiteManager {
    QSqlDatabase db;
    int limit;
public:
    SQLiteManager(const QString &path, int limit);
    ~SQLiteManager();

    void createTable();
    void putValue(const QString& key, const QString& value);
    QString getValue(const QString& key);
};

#endif // DATABASE_H
