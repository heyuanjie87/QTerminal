#-------------------------------------------------
#
# Project created by QtCreator 2017-01-04T14:16:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test
TEMPLATE = app

INCLUDEPATH += ../QTermWidget

SOURCES += main.cpp\
        mainwindow.cpp \
    dialog.cpp \
    ../QTermWidget/QTermScreen.cpp \
    ../QTermWidget/QTermWidget.cpp

HEADERS  += mainwindow.h \
    dialog.h \
    ../QTermWidget/QTermScreen.h \
    ../QTermWidget/QTermWidget.h

FORMS    += mainwindow.ui \
    dialog.ui
