/*
#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H

#include <QObject>
#include <QWebSocket>
#include <QWebSocketServer>
#include <QJsonObject>

class WebSocketServer : public QObject
{
    Q_OBJECT
public:
    WebSocketServer(quint16 port, bool debug, QObject *parent = nullptr);
    ~WebSocketServer();

    int start();
    bool m_debug;

private Q_SLOTS:
    void onNewConnection();
    void processTextMessage(QString message);
    void processBinaryMessage(QByteArray message);
    void socketDisconnected();
    void onSslErrors(const QList<QSslError> &errors);

private:
    QWebSocketServer *m_pWebSocketServer;
    QList<QWebSocket *> m_clients;
};

#endif // WEBSOCKETSERVER_H
*/
