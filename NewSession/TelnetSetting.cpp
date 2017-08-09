#include "TelnetSetting.h"
#include "ui_TelnetSetting.h"

TelnetSetting::TelnetSetting(QWidget *parent) :
    Setting(parent),
    ui(new Ui::TelnetSetting)
{
    ui->setupUi(this);
}

TelnetSetting::~TelnetSetting()
{
    delete ui;
}

void TelnetSetting::getSetting(SesParam &ns)
{
    ns["host"] = ui->host->text();
    ns["port"] = ui->port->text();
}
