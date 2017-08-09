#include "TelnetTerm.h"
#include "ui_TelnetTerm.h"

#include "qttelnet.h"

TelnetTerm::TelnetTerm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TelnetTerm)
{
    ui->setupUi(this);

    initTelnet();
    initTerm();

    statusBar()->addWidget(ui->btConnect);
}

TelnetTerm::~TelnetTerm()
{
    delete ui;
}

void TelnetTerm::setSettings(SesParam &ss)
{
    settings = ss;
}

void TelnetTerm::initTerm()
{
    term = new QTermWidget;

    connect(term, SIGNAL(outData(QByteArray)), this, SLOT(writeData(QByteArray)));

    setCentralWidget(term);
}

void TelnetTerm::initTelnet()
{
    telnet = new QtTelnet;

    connect(telnet, SIGNAL(message(QString)), this, SLOT(readData(QString)));
}

void TelnetTerm::writeData(const QByteArray &data)
{
    telnet->sendData(data);
}

void TelnetTerm::readData(const QString &data)
{
    term->putData(data.toLocal8Bit());
}

void TelnetTerm::on_btConnect_clicked()
{
    QString host = settings["host"];
    short port = settings["port"].toShort();

    telnet->connectToHost(host, port);
}
