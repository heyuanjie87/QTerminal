#include "KconfigSetting.h"
#include "ui_KconfigSetting.h"

#include <QFileDialog>

KconfigSetting::KconfigSetting(QWidget *parent) :
    Setting(parent),
    ui(new Ui::KconfigSetting)
{
    ui->setupUi(this);
}

KconfigSetting::~KconfigSetting()
{
    delete ui;
}

void KconfigSetting::getSetting(SesParam &ns)
{
    ns["file"] = ui->file->text();
    ns["env"] = ui->env->text();
    ns["cmd"] = ui->cmd->text();
}

void KconfigSetting::on_find_clicked()
{
    QString s = QFileDialog::getOpenFileName(this, QString("kconfig"));
    if (s.isEmpty())
        return;

    ui->file->setText(s);
}
