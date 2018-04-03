#include "NewSession.h"
#include "ui_NewSession.h"
#include <QDateTime>

#include "SerialSetting.h"
#include "TelnetSetting.h"
#include "NetAssistSetting.h"
#include "KconfigSetting.h"

NewSession::NewSession(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewSession)
{
    ui->setupUi(this);

    SerialSetting *sset = new SerialSetting;

    sset->setParent(ui->fmParam);
    ui->sesType->setCurrentRow(0);

    wSetting["串口终端"] = sset;
    wSetting["telnet"] = new TelnetSetting;
    wSetting["网络助手"] = new NetAssistSetting;
    wSetting["Kconfig"] = new KconfigSetting;
}

NewSession::~NewSession()
{
    delete ui;
    wSetting.clear();
}

void NewSession::getSetting(Session &s)
{
    QString type;
    Setting *cur;

    type = ui->sesType->currentItem()->text();
    cur = wSetting[type];
    s.type = type;
    s.name = ui->sesName->text();
    s.show = "1";
    if (cur != NULL)
    {
        cur->getSetting(s.param);
    }
    makeID(s.id);
}

void NewSession::makeID(QString &id)
{
    QDateTime dt;

    dt = dt.currentDateTime();
    id = id.sprintf("%d", dt.toTime_t());
}

void NewSession::on_sesType_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    Setting *cur, *pre = NULL;

    cur = wSetting[current->text()];
    if (previous)
    {
        pre = wSetting[previous->text()];
    }

    if (pre != NULL)
    {
        pre->hide();
    }

    if (cur != NULL)
    {
        cur->setParent(ui->fmParam);
        cur->show();
    }
}
