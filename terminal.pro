QT += widgets serialport sql

TARGET = QTerm
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    settingsdialog.cpp \
    SendSave/SendSave.cpp \
    SendSave/SSWorker.cpp \
    QTermWidget/QTermScreen.cpp \
    QTermWidget/QTermWidget.cpp \
    Modem/Modem.cpp \
    Modem/Ymodem.cpp \
    Modem/crc16.c

HEADERS += \
    mainwindow.h \
    settingsdialog.h \
    SendSave/SendSave.h \
    SendSave/SSWorker.h \
    QTermWidget/QTermScreen.h \
    QTermWidget/QTermWidget.h \
    Modem/Modem.h \
    Modem/Ymodem.h \
    Modem/crc.h

FORMS += \
    mainwindow.ui \
    settingsdialog.ui \
    SendSave/SendSave.ui \
    Modem/modem.ui

RESOURCES += \
    terminal.qrc
