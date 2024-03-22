#include "websocketeasyserver.h"
#include "QtWebSockets/qwebsocketserver.h"
#include "QtWebSockets/qwebsocket.h"
#include "database.h"
#include "qjsondocument.h"
#include <QtCore/QDebug>

QT_USE_NAMESPACE

//! [constructor]
WebSocketEasyServer::WebSocketEasyServer(quint16 port, bool debug, QObject *parent) :
    QObject(parent),
    m_pWebSocketServer(new QWebSocketServer(QStringLiteral("Echo Server"),
                                            QWebSocketServer::NonSecureMode, this)),
    m_debug(debug)
{
    this->port = port;
}

bool WebSocketEasyServer::start()
{
    if (m_pWebSocketServer->listen(QHostAddress::Any, port)) {
        if (m_debug)
            qDebug() << "Echoserver listening on port" << port;
        connect(m_pWebSocketServer, &QWebSocketServer::newConnection,
                this, &WebSocketEasyServer::onNewConnection);
        connect(m_pWebSocketServer, &QWebSocketServer::closed, this, &WebSocketEasyServer::closed);
        return true;
    }
    return false;
}
//! [constructor]

WebSocketEasyServer::~WebSocketEasyServer()
{
    m_pWebSocketServer->close();
    qDeleteAll(m_clients.begin(), m_clients.end());
}

void WebSocketEasyServer::broadcast(const QString &msg, const QWebSocket *exclude)
{
    for(auto & client : m_clients) {
        if(client == exclude)
            continue;
        client->sendTextMessage(msg);
    }
}

//! [onNewConnection]
void WebSocketEasyServer::onNewConnection()
{
    QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();

    connect(pSocket, &QWebSocket::textMessageReceived, this, &WebSocketEasyServer::processTextMessage);
    connect(pSocket, &QWebSocket::binaryMessageReceived, this, &WebSocketEasyServer::processBinaryMessage);
    connect(pSocket, &QWebSocket::disconnected, this, &WebSocketEasyServer::socketDisconnected);

    m_clients << pSocket;
}
//! [onNewConnection]

//! [processTextMessage]
void WebSocketEasyServer::processTextMessage(QString message)
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (m_debug)
        qDebug() << "Message received:" << message;

    if(message == "ping")
        return;

    QJsonDocument value = QJsonDocument::fromJson(message.toUtf8());
    QString ip;

    // Checking if Document has object or not
    if(!value.isObject()){
        qDebug() << "Document is not an object";
        return;
    }

    if (value["TYPE"].toString() == "EMERGENCY")
        ip = value["IP"].toString();
    else
        return;

    qDebug() << "Received message from client: " << ip;

    // Send the message back to the client
 // auto db = SQLiteManager("EmergencyAppAPIServer.db", 1000);
 // auto data = db.getValue(ip);
    QString broad_msg = "{\"id\": 0, \"FLOOR\": \"Floor 3\", \"ROOM\": \"Room B41\", \"TYPE\": \"FIRE\"}";

    // Broadcast the message to all connected clients
    this->broadcast(broad_msg, pClient);

    if (value["TYPE"].toString() == "REQUEST")
        return;

}
//! [processTextMessage]

//! [processBinaryMessage]
void WebSocketEasyServer::processBinaryMessage(QByteArray message)
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (m_debug)
        qDebug() << "Binary Message received:" << message;
    if (pClient) {
        pClient->sendBinaryMessage(message);
    }
}
//! [processBinaryMessage]

//! [socketDisconnected]
void WebSocketEasyServer::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (m_debug)
        qDebug() << "socketDisconnected:" << pClient;
    if (pClient) {
        m_clients.removeAll(pClient);
        pClient->deleteLater();
    }
}
//! [socketDisconnected]
