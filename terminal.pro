QT += widgets serialport sql

TARGET = QTerm
TEMPLATE = app

SOURCES += \
    simple/main.cpp \
    simple/mainwindow.cpp \
    simple/settingsdialog.cpp \
    SendSave/SendSave.cpp \
    SendSave/SSWorker.cpp \
    QTermWidget/QTermScreen.cpp \
    QTermWidget/QTermWidget.cpp \
    Modem/Modem.cpp \
    Modem/Ymodem.cpp \
    Modem/crc16.c

HEADERS += \
    simple/mainwindow.h \
    simple/settingsdialog.h \
    SendSave/SendSave.h \
    SendSave/SSWorker.h \
    QTermWidget/QTermScreen.h \
    QTermWidget/QTermWidget.h \
    Modem/Modem.h \
    Modem/Ymodem.h \
    Modem/crc.h

FORMS += \
    simple/mainwindow.ui \
    simple/settingsdialog.ui \
    SendSave/SendSave.ui \
    Modem/modem.ui

RESOURCES += \
    simple/terminal.qrc
