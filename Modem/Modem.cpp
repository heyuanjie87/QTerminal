#include "Modem.h"
#include "ui_modem.h"

#include "Ymodem.h"

#include <QMessageBox>

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
    fmt = fmt.fromLocal8Bit("%1%").arg(QString::number(p, 'f', 2));
    ui->progress->setValue((int)p);
    ui->progress->setFormat(fmt);

    fmt = fmt.sprintf("速度:%.2fKB/S 剩余:%d/%dKB",
                      speed/1024, remain/1024, total/1024);
    showStatus(fmt);
}

void Modem::startTransfer(char type)
{
    showTransfer(1, 1, 0);
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

void Modem::showStatus(QString &s)
{
    ui->lbmsg->setText(s);
}

void Modem::closed()
{
    emit exitTransfer();
}

void Modem::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton button;

    button = QMessageBox::question(this, tr("退出程序"),
        QString(tr("警告:任务正在运行中，是否结束操作退出?")),
        QMessageBox::Yes | QMessageBox::No);

    if (button == QMessageBox::No)
    {
        event->ignore();  //忽略退出信号，程序继续运行
    }
    else if (button == QMessageBox::Yes)
    {
        event->accept();  //接受退出信号，程序退出
        ym->close();
    }
}

