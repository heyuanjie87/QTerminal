#include "TelnetTerm.h"
#include "ui_TelnetTerm.h"

#include "qttelnet.h"

TelnetTerm::TelnetTerm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TelnetTerm)
{
    ui->setupUi(this);

    telnet = new QtTelnet;
}

TelnetTerm::~TelnetTerm()
{
    delete ui;
}

void TelnetTerm::on_btConnect_clicked()
{
    telnet->connectToHost("localhost");
}
