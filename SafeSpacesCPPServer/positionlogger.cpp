#include "positionlogger.h"
/*
PositionLogger::PositionLogger() {



    qDebug() << "PositionLogger";

    QNetworkAccessManager manager;
    QByteArray apiKey = "AE896EB3EAB0446887153C2114272A2F"; // read from file, or request input from user.

    // Set the request URL and headers
    QNetworkRequest request(QUrl("https://partners.dnaspaces.io/api/partners/v1/firehose/events"));
    request.setRawHeader("X-API-Key", apiKey);  // Replace apiKey with your key


    qDebug() << "Send the GET request";
    // Send the GET request
    QNetworkReply *reply = manager.get(request);

    while(true) {

        // Wait for the reply
        qDebug() << "Wait for the reply";
        QEventLoop loop;
        QObject::connect(reply, SIGNAL(readyRead()), &loop, SLOT(quit()));
        loop.exec();

        // Check for errors
        if (reply->error()) {
            qDebug() << "Error:" << reply->errorString();
            return;
        }

        QTextStream in(reply);
        QString line = in.readLine();
        qDebug() << line;

    }


    // Parse lines from the response
    QString line;
    QTextStream in(reply);
    qDebug() << "Starting Stream";
    while (!in.atEnd()) {
        line = in.readLine();
        qDebug() << line;
    }

    return;

}
*/
#include "positionlogger.h"
#include <iostream>

PositionLogger::PositionLogger(const bool &debug)
    : db("C:/Users/Markus/Nextcloud/CPP-Projekte/Tests/EmergencyAppServer/db2.sqlite", 1000)
    , debug(debug)
{
    apiKey = "AE896EB3EAB0446887153C2114272A2F"; // read from file, or request input from user.
#ifdef GUI
    w.show();
    w.showFullScreen();
#endif
}

PositionLogger::~PositionLogger()
{
    if(reply) {
        reply->abort();
        delete reply;
    }

}

void PositionLogger::startRecieving()
{
    if(debug)
        qDebug() << "startRecieving";
    QNetworkRequest request(QUrl("https://partners.dnaspaces.io/api/partners/v1/firehose/events"));
    request.setRawHeader("X-API-Key", apiKey);  // Replace apiKey with your key
    reply = this->get(request);
    QObject::connect(reply, SIGNAL(readyRead()), this, SLOT(newData()));
    QObject::connect(reply, SIGNAL(finished()), this, SLOT(finishedRecieving()));

}

void PositionLogger::finishedRecieving()
{
    if(reply) {
        QObject::disconnect(reply, SIGNAL(readyRead()), this, SLOT(newData()));
        QObject::disconnect(reply, SIGNAL(finished()), this, SLOT(finishedRecieving()));
        reply->deleteLater();
        reply = nullptr;
    }
    //restart!
    QThread::sleep(1);
    startRecieving();
}

void PositionLogger::newData()
{
    // Check for errors
    if (reply->error()) {
        qDebug() << "Error:" << reply->errorString();
        return;
    }


    QString jsonString = reply->readLine().replace("\n", "");
    if(!jsonString.contains("DEVICE_LOCATION_UPDATE")) {
        if(this->debug)
            std::cout << "." << std::flush;
        return;
    }


    // Parsing data into Json Document
    QJsonDocument doc = QJsonDocument::fromJson(jsonString.toUtf8());

    // Checking if Document has object or not
    if(!doc.isObject()){
        qDebug() << "Document is not an object";
        return;
    }

    // fetching the object
    QJsonObject obj = doc.object();

    // accessing the nested JsonObject
    QJsonObject deviceLocationUpdate = obj["deviceLocationUpdate"].toObject();

    // then simply fetching the ipv4 value
    QString ipv4 = deviceLocationUpdate["ipv4"].toString();

    if(!ipv4.isEmpty()) {
        db.putValue(ipv4, jsonString);
        qDebug() << "\n";
    }

#ifdef GUI

    unsigned x = deviceLocationUpdate["xPos"].toDouble();
    unsigned y = deviceLocationUpdate["yPos"].toDouble();

    if(this->debug)
        qDebug() << "\nEDITED: " << ipv4 << " POS: " << x << " - " << y;
    w.addPoint(ipv4, x, y);
#endif

}
