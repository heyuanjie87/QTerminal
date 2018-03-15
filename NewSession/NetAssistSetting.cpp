#include "NetAssistSetting.h"
#include "ui_NetAssistSetting.h"

NetAssistSetting::NetAssistSetting(QWidget *parent) :
    Setting(parent),
    ui(new Ui::NetAssistSetting)
{
    ui->setupUi(this);
}

NetAssistSetting::~NetAssistSetting()
{
    delete ui;
}

void NetAssistSetting::getSetting(SesParam &ns)
{
    ns["ptype"] = ui->ptype->currentText();
    ns["lport"] = ui->lport->text();
    ns["rhost"] = ui->rhost->text();
}
