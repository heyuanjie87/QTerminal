#include "SerialTerm.h"
#include "ui_SerialTerm.h"

#include "QTermWidget/QTermWidget.h"
#include "SendSave/SendSave.h"

SerialTerm::SerialTerm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SerialTerm)
{
    ui->setupUi(this);

    initTerm();

    statusBar()->addWidget(ui->btConnect);

    initSendSave();
    initSerial();

    statusBar()->addWidget(ui->lbParam);
}

SerialTerm::~SerialTerm()
{
    delete ui;
    delete serial;
    delete dlgSS;
    delete term;
}

void SerialTerm::initTerm()
{
    term = new QTermWidget;

    connect(term, SIGNAL(outData(QByteArray)), this, SLOT(writeData(QByteArray)));
    setCentralWidget((QWidget*)term);
}

void SerialTerm::initSendSave()
{
    dlgSS = new SendSave;

    statusBar()->addWidget(dlgSS->toolButton(0));
    statusBar()->addWidget(dlgSS->toolButton(1));
    statusBar()->addWidget(dlgSS->toolButton(2));
    statusBar()->addWidget(dlgSS->toolButton(3));

    connect(dlgSS, SIGNAL(outData(QByteArray)), this, SLOT(writeData(QByteArray)));
}

void SerialTerm::initSerial()
{
    serial = new QSerialPort;

    connect(serial, SIGNAL(readyRead()), this, SLOT(readData()));
    connect(serial, SIGNAL(error(QSerialPort::SerialPortError)),
            this, SLOT(error(QSerialPort::SerialPortError)));
}

void SerialTerm::error(QSerialPort::SerialPortError e)
{
    if (e == QSerialPort::PermissionError)
    {
        ui->btConnect->setText(QString("连接"));
    }
}

bool SerialTerm::openSerial()
{
    bool ret;

    serial->setPortName(settings["dev"]);
    serial->setBaudRate(settings["speed"].toInt());

    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setDataBits(QSerialPort::Data8);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    ret = serial->open(QIODevice::ReadWrite);

    return ret;
}

void SerialTerm::setSettings(SesParam &ss, QString id)
{
    settings = ss;
    QString p;

    p = ss["dev"] + "," + ss["speed"];
    ui->lbParam->setText(p);
    id += ".dblite";
    dlgSS->connectDb(id);
}

void SerialTerm::writeData(const QByteArray &data)
{
    serial->write(data);
}

void SerialTerm::readData()
{
    QByteArray data;

    data = serial->readAll();

    term->putData(data);
}

void SerialTerm::on_btConnect_clicked()
{
    if (serial->isOpen())
    {
        serial->close();
        ui->btConnect->setText(QString("连接"));
    }
    else if (openSerial())
    {
        ui->btConnect->setText(QString("断开"));
    }
}
