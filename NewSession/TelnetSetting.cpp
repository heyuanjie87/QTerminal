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

void TelnetSetting::getSetting(SessionSetting &ns)
{

}
