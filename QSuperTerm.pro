#-------------------------------------------------
#
# Project created by QtCreator 2017-03-21T19:23:08
#
#-------------------------------------------------

QT       += core gui serialport network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QSuperTerm
TEMPLATE = app

FORMS += \
    SuperTerm/mainwindow.ui \
    NewSession/NewSession.ui \
    NewSession/SerialSetting.ui \
    NewSession/TelnetSetting.ui \
    Telnet/TelnetTerm.ui

HEADERS += \
    SuperTerm/mainwindow.h \
    NewSession/NewSession.h \
    NewSession/SerialSetting.h \
    NewSession/Setting.h \
    NewSession/TelnetSetting.h \
    Serial/SerialTerm.h \
    QTermWidget/QTermScreen.h \
    QTermWidget/QTermWidget.h \
    NewSession/SessionWindow.h \
    Telnet/qttelnet.h \
    Telnet/TelnetTerm.h

SOURCES += \
    SuperTerm/main.cpp \
    SuperTerm/mainwindow.cpp \
    NewSession/NewSession.cpp \
    NewSession/SerialSetting.cpp \
    NewSession/Setting.cpp \
    NewSession/TelnetSetting.cpp \
    Serial/SerialTerm.cpp \
    QTermWidget/QTermScreen.cpp \
    QTermWidget/QTermWidget.cpp \
    NewSession/SessionWindow.cpp \
    Telnet/qttelnet.cpp \
    Telnet/TelnetTerm.cpp

