QT       += core gui
QT       += core
QT       += core gui charts
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    creategraph.cpp \
    jsonparserchooser.cpp \
    jsonparserchooser.cpp \
    controller.cpp \
    jsonnetworker.cpp \
    main.cpp \
    mainwindow.cpp \
    model.cpp

HEADERS += \
    jsonparserchooser.h \
    jsonparserchooser.h \
    mainwindow.h \
    controller.h \
    jsonnetworker.h \
    mainwindow.h \
    model.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
