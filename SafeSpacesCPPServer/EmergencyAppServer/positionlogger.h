#ifndef POSITIONLOGGER_H
#define POSITIONLOGGER_H

#include "database.h"

#ifdef GUI
#include "mainwindow.h"
#endif

#include <QNetworkReply>
#include <QObject>
#include <QThread>

class PositionLogger : public QNetworkAccessManager
{
    Q_OBJECT
public:
    PositionLogger(const bool &debug);
    ~PositionLogger();

    void startRecieving();
#ifdef GUI
    MainWindow w;
#endif
    QNetworkReply *reply;
    QByteArray apiKey;
    SQLiteManager db;
    bool debug;

public slots:
    void newData();
    void finishedRecieving();

};

#endif // POSITIONLOGGER_H
