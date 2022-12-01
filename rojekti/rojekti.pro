QT       += core gui
QT       += core
QT       += core gui
QT       += charts
QT       += network
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    creategraph.cpp \
    controller.cpp \
    filecreator.cpp \
    ijsonparser.cpp \
    jsonroadconditionparser.cpp \
    jsonroadmaintenanceparser.cpp \
    jsontrafficmessageparser.cpp \
    main.cpp \
    mainwindow.cpp \
    model.cpp \
    networker.cpp \
    urlbuilder.cpp \
    xmlparser.cpp

HEADERS += \
    filecreator.h \
    ijsonparser.h \
    jsonroadconditionparser.h \
    jsonroadmaintenanceparser.h \
    jsontrafficmessageparser.h \
    mainwindow.h \
    controller.h \
    mainwindow.h \
    model.h \
    networker.h \
    urlbuilder.h \
    xmlparser.h

FORMS += \
    mainwindow.ui

QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.15

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
