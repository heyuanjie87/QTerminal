#include "SerialSetting.h"
#include "ui_SerialSetting.h"

#include <QtSerialPort>

SerialSetting::SerialSetting(QWidget *parent) :
    Setting(parent),
    ui(new Ui::SerialSetting)
{
    ui->setupUi(this);

    initParam();
    updateDevice();
}

SerialSetting::~SerialSetting()
{
    delete ui;
}

void SerialSetting::initParam()
{
    ui->speed->addItem(QStringLiteral("9600"), QSerialPort::Baud9600);
    ui->speed->addItem(QStringLiteral("19200"), QSerialPort::Baud19200);
    ui->speed->addItem(QStringLiteral("38400"), QSerialPort::Baud38400);
    ui->speed->addItem(QStringLiteral("115200"), QSerialPort::Baud115200);
    ui->speed->setCurrentIndex(3);

    ui->parity->addItem(QStringLiteral("None"), QSerialPort::NoParity);
    ui->parity->addItem(QStringLiteral("Even"), QSerialPort::EvenParity);
    ui->parity->addItem(QStringLiteral("Odd"), QSerialPort::OddParity);

    ui->stopbits->addItem(QStringLiteral("1"), QSerialPort::OneStop);
    ui->stopbits->addItem(QStringLiteral("2"), QSerialPort::TwoStop);
}

void SerialSetting::updateDevice()
{
    QStringList list;

    ui->devname->clear();

    list << QString(tr("刷新"));

    ui->devname->addItem(list.first(), list);

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QStringList list;

        list << info.portName();

        ui->devname->addItem(list.first(), list);
    }

    if (ui->devname->count() != 1)
    {
        ui->devname->setCurrentIndex(1);
    }
}

void SerialSetting::getSetting(SesParam &ns)
{
    ns["dev"] = ui->devname->currentText();
    ns["speed"] = ui->speed->currentText();
}

void SerialSetting::on_devname_activated(int index)
{
    if (index == 0)
    {
        updateDevice();
    }
}
