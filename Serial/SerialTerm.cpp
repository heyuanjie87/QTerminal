#include "SerialTerm.h"
#include "ui_SerialTerm.h"

#include "QTermWidget/QTermWidget.h"
#include "SendSave/SendSave.h"

#include <QSerialPort>

SerialTerm::SerialTerm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SerialTerm)
{
    ui->setupUi(this);

    term = new QTermWidget;
    setCentralWidget((QWidget*)term);

    statusBar()->addWidget(ui->btConnect);
    statusBar()->addWidget(ui->btRecord);

    initSendSave();
    initSerial();
}

SerialTerm::~SerialTerm()
{
    delete ui;
}

void SerialTerm::initSendSave()
{
    dlgSS = new SendSave;

    statusBar()->addWidget(dlgSS->toolButton(0));
    statusBar()->addWidget(dlgSS->toolButton(1));
    statusBar()->addWidget(dlgSS->toolButton(2));

}

void SerialTerm::initSerial()
{
    serial = new QSerialPort;
}

bool SerialTerm::openSerial()
{
    bool ret;

    serial->setPortName(settings["dev"]);
    serial->setBaudRate(settings["dev"].toInt());

    ret = serial->open(QIODevice::ReadWrite);

    return ret;
}

void SerialTerm::setSettings(SessionSetting &ss)
{
    settings = ss;
}

void SerialTerm::on_btRecord_clicked()
{
    dlgSS->show();
    dlgSS->activateWindow();
}

void SerialTerm::on_btConnect_clicked()
{
    if (serial->isOpen())
    {
        serial->close();
        ui->btConnect->setWindowTitle(QString("连接"));
    }
    else if (openSerial())
    {
        ui->btConnect->setWindowTitle(QString("断开"));
    }
}
