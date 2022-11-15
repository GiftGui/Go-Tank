QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += D:\sdk\asio-1.24.0\include

SOURCES += \
    BrickWall.cpp \
    Bullet.cpp \
    GameDialog.cpp \
    MyScene.cpp \
    Tank.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    BrickWall.h \
    Bullet.h \
    GameDialog.h \
    MMO_Common.h \
    MainWindow.h \
    MyScene.h \
    Tank.h \
    olcPGEX_Network.h

FORMS += \
    MainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
