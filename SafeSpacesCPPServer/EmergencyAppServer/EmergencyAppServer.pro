QT = core sql websockets #gui
#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        database.cpp \
        main.cpp \
        mainwindow.cpp \
        positionlogger.cpp \
        websocketeasyserver.cpp \
        websocketserver.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    database.h \
    mainwindow.h \
    positionlogger.h \
    websocketeasyserver.h \
    websocketserver.h

RESOURCES += \
    ressources.qrc
