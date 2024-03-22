#ifndef WEBSOCKETEASYSERVER_H
#define WEBSOCKETEASYSERVER_H

#include <QObject>
#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QByteArray>

QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)

class WebSocketEasyServer : public QObject
{
    Q_OBJECT
public:
    explicit WebSocketEasyServer(quint16 port, bool debug = false, QObject *parent = nullptr);
    bool start();
    ~WebSocketEasyServer();


    void broadcast(const QString &msg, const QWebSocket* exclude);

Q_SIGNALS:
    void closed();

private Q_SLOTS:
    void onNewConnection();
    void processTextMessage(QString message);
    void processBinaryMessage(QByteArray message);
    void socketDisconnected();

private:
    QWebSocketServer *m_pWebSocketServer;
    QList<QWebSocket *> m_clients;
    bool m_debug;
    quint16 port;
};
#endif // WEBSOCKETEASYSERVER_H
