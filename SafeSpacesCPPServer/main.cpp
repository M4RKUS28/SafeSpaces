#include "positionlogger.h"
//#include "websocketserver.h"
#include "websocketeasyserver.h"
#ifdef GUI
#include <QApplication>
#else
#include <QCoreApplication>
#endif

int main(int argc, char *argv[])
{
#ifdef GUI
    QApplication a(argc, argv);
#else
    QCoreApplication a(argc, argv);
#endif

    bool debug = true;
    int port = 8088;
    WebSocketEasyServer webserver(port, debug);
    PositionLogger logger(debug);

    if(!webserver.start()) {
        qDebug() << "Starting webserver failed!";
        return 1;
    }
    qDebug() << "Started webserver on port " << port;

    logger.startRecieving();
    qDebug() << "Started Logger!";


    return a.exec();
}
