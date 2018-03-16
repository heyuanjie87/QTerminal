#include "NetAssist.h"
#include "ui_NetAssist.h"

#include "SendSave/SendSave.h"

#include <QUdpSocket>
#include <QNetworkInterface>

NetAssist::NetAssist(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NetAssist)
{
    ui->setupUi(this);
    udpServer = NULL;
    initSendSave();
}

NetAssist::~NetAssist()
{
    delete ui;
    delete dlgSS;
    delete udpServer;
}

void NetAssist::setSettings(Session &ss)
{
    QString id;

    netParam = ss;

    id = ss.id + ".dblite";
    dlgSS->connectDb(id);

    initNet(ss);
}

void NetAssist::initSendSave()
{
    dlgSS = new SendSave;

    statusBar()->addWidget(dlgSS->toolButton(0));
    statusBar()->addWidget(dlgSS->toolButton(1));
    statusBar()->addWidget(dlgSS->toolButton(2));
    statusBar()->addWidget(dlgSS->toolButton(3));

    connect(dlgSS, SIGNAL(outData(QByteArray)), this, SLOT(recordSend(QByteArray)));
}

void NetAssist::initNet(Session &ss)
{
    QList<QHostAddress> ipAL = QNetworkInterface::allAddresses();

    ui->lport->setValue(ss.param["lport"].toUShort());
    ui->ptype->setText(ss.param["ptype"]);
    foreach (QHostAddress ip, ipAL)
    {
        bool ok;

        ip.toIPv4Address(&ok);
        if (ok)
            ui->lip->addItem(ip.toString());
    }
    udpServer = new QUdpSocket(this);
    ui->cbrip->setCurrentText(ss.param["rhost"]);
    connect(udpServer, SIGNAL(readyRead()), this, SLOT(udpServerReadData()));
}

void NetAssist::udpServerReadData()
{
    QHostAddress senderServerIP;
    quint16 senderServerPort;
    QByteArray data;
    QString buffer;

    do
    {
        data.resize(udpServer->pendingDatagramSize());
        udpServer->readDatagram(data.data(), data.size(), &senderServerIP, &senderServerPort);

        buffer = data.toStdString().c_str();
        ui->display->appendPlainText(buffer);
    } while (udpServer->hasPendingDatagrams());
}

void NetAssist::recordSend(QByteArray buf)
{
    QString str;

    str = buf;
    ui->pesend->clear();
    ui->pesend->appendPlainText(str);

    udpSend(buf);
}

void NetAssist::on_open_clicked()
{
    bool ok;
    uint16_t lport;

    if (ui->open->text() == "打开")
    {
        QHostAddress ha(ui->lip->currentText());

        lport = ui->lport->text().toUShort();
        udpServer->abort();
        ok = udpServer->bind(ha, lport);
        if (ok)
            ui->open->setText("关闭");
    }
    else
    {
        udpServer->abort();
        ui->open->setText("打开");
    }
}

void NetAssist::udpSend(QByteArray &buf)
{
    QString ip, port;
    QStringList list;

    list = ui->cbrip->currentText().split(":");
    ip = list.at(0);
    port = list.at(1);

    udpServer->writeDatagram(buf, QHostAddress(ip), port.toUShort());
}

void NetAssist::on_rcvclear_clicked()
{
    ui->display->clear();
}

void NetAssist::on_btsend_clicked()
{
    QByteArray buf;

    buf = ui->pesend->toPlainText().toStdString().c_str();
    udpSend(buf);
}
