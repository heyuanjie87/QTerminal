#include "Modem.h"
#include "ui_modem.h"

#include "Ymodem.h"

Modem::Modem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Modem)
{
    ui->setupUi(this);

    ym = new Ymodem(this);
    connect(ym, &ym->showTransfer, this, &this->showTransfer);
    connect(ym, &ym->finished, this, &this->closed);
}

Modem::~Modem()
{
    delete ui;
}

void Modem::getFile(QString &name)
{
    name = filename;
}

void Modem::setFile(QString &name)
{
    filename = name;
}

void Modem::showTransfer(int total, int remain, float speed)
{
    float p;
    QString fmt;

    p = ((total - remain)/(float)total) * 100;
    fmt = fmt.fromLocal8Bit("%1%").arg(QString::number(p, 'f', 1));
    ui->progress->setValue((int)p);
    ui->progress->setFormat(fmt);
}

void Modem::startTransfer(char type)
{
    show();
    ym->start();
}

void Modem::putData(const QByteArray &data)
{
    ym->put(data);
}

void Modem::showStatus(const char *s)
{
    ui->lbmsg->setText(s);
}

void Modem::closed()
{
    emit exitTransfer();
}
