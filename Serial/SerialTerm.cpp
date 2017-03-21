#include "SerialTerm.h"

#include <QtSerialPort/QSerialPort>

SerialTerm::SerialTerm(QWidget *parent)
{
    term = new QTermWidget;
    serial = new QSerialPort;

    connect(serial, SIGNAL(readyRead()), this, SLOT(readData()));
    connect(term, SIGNAL(outData(QByteArray)), this, SLOT(writeData(QByteArray)));
}

QWidget* SerialTerm::getWindow()
{
    return term;
}

void SerialTerm::setSetting(const SessionSetting &ss)
{
    settings = ss;
}

void SerialTerm::open()
{

}

void SerialTerm::close()
{

}

void SerialTerm::readData()
{
    QByteArray data = serial->readAll();

    term->putData(data);
}

void SerialTerm::writeData(const QByteArray &data)
{
    serial->write(data);
}
