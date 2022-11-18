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
    jsonnetworker.cpp \
    jsonroadconditionparser.cpp \
    jsonroadmaintenanceparser.cpp \
    jsontrafficmessageparser.cpp \
    main.cpp \
    mainwindow.cpp \
    model.cpp \
    xmlparser.cpp

HEADERS += \
    filecreator.h \
    jsonroadconditionparser.h \
    jsonroadmaintenanceparser.h \
    jsontrafficmessageparser.h \
    mainwindow.h \
    controller.h \
    jsonnetworker.h \
    mainwindow.h \
    model.h \
    xmlparser.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
