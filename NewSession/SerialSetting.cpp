#include "SerialSetting.h"
#include "ui_SerialSetting.h"

SerialSetting::SerialSetting(QWidget *parent) :
    Setting(parent),
    ui(new Ui::SerialSetting)
{
    ui->setupUi(this);
}

SerialSetting::~SerialSetting()
{
    delete ui;
}

void SerialSetting::getSetting(SessionSetting &ns)
{
    ns["dev"] = "com5";
    ns["speed"] = "115200";
}
