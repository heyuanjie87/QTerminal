#-------------------------------------------------
#
# Project created by QtCreator 2017-03-21T19:23:08
#
#-------------------------------------------------

QT       += core gui serialport sql network xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QSuperTerm
TEMPLATE = app
DESTDIR  = bin

FORMS += \
    SuperTerm/mainwindow.ui \
    NewSession/NewSession.ui \
    NewSession/SerialSetting.ui \
    NewSession/TelnetSetting.ui \
    Telnet/TelnetTerm.ui \
    Serial/SerialTerm.ui \
    SendSave/SendSave.ui \
    Console/console.ui \
    NetAssist/NetAssist.ui \
    NewSession/NetAssistSetting.ui \
    NewSession/KconfigSetting.ui

HEADERS += \
    SuperTerm/mainwindow.h \
    NewSession/NewSession.h \
    NewSession/SerialSetting.h \
    NewSession/Setting.h \
    NewSession/TelnetSetting.h \
    QTermWidget/QTermScreen.h \
    QTermWidget/QTermWidget.h \
    NewSession/SessionWindow.h \
    Telnet/qttelnet.h \
    Telnet/TelnetTerm.h \
    Serial/SerialTerm.h \
    SendSave/SendSave.h \
    SendSave/SSWorker.h \
    SuperTerm/projectfile.h \
    NewSession/nstypes.h \
    Console/Console.h \
    Console/pty.h \
    NetAssist/NetAssist.h \
    NewSession/NetAssistSetting.h \
    KConfig/expr.h \
    KConfig/list.h \
    KConfig/lkc.h \
    KConfig/lkc_proto.h \
    KConfig/qconf.h \
    KConfig/QKconfig.h \
    NewSession/KconfigSetting.h


SOURCES += \
    SuperTerm/main.cpp \
    SuperTerm/mainwindow.cpp \
    NewSession/NewSession.cpp \
    NewSession/SerialSetting.cpp \
    NewSession/Setting.cpp \
    NewSession/TelnetSetting.cpp \
    QTermWidget/QTermScreen.cpp \
    QTermWidget/QTermWidget.cpp \
    NewSession/SessionWindow.cpp \
    Telnet/qttelnet.cpp \
    Telnet/TelnetTerm.cpp \
    Serial/SerialTerm.cpp \
    SendSave/SendSave.cpp \
    SendSave/SSWorker.cpp \
    SuperTerm/projectfile.cpp \
    Console/Console.cpp \
    Console/pty.cpp \
    NetAssist/NetAssist.cpp \
    NewSession/NetAssistSetting.cpp \
    KConfig/qconf.cpp \
    KConfig/QKconfig.cpp \
    KConfig/confdata.c \
    KConfig/expr.c \
    KConfig/images.c \
    KConfig/menu.c \
    KConfig/symbol.c \
    KConfig/util.c \
    KConfig/zconf.hash.c \
    KConfig/zconf.lex.c \
    KConfig/zconf.tab.c \
    NewSession/KconfigSetting.cpp

win:
{
LIBS += -L$$PWD/./ -lwinpty
}
LIBS += -lregex
