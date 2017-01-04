#include "SendSave.h"
#include "ui_SendSave.h"
#include "SSWorker.h"

#include <QSqlDatabase>

#include <sstream>
#include <iostream>
using namespace std;

SendSave::SendSave(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SendSave)
{
    ui->setupUi(this);

    tableInit();

    worker = new SSWorker(this);
    worker->start();
}

SendSave::~SendSave()
{
    delete ui;
    delete worker;
}

void SendSave::tableInit()
{
    ui->tbSave->setColumnCount(3);

    QStringList header;

    header << "名称" << "内容" << "换行符";
    ui->tbSave->setHorizontalHeaderLabels(header);

    ui->tbSave->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tbSave->horizontalHeader()->resizeSection(0, 60);
    ui->tbSave->horizontalHeader()->resizeSection(1, 160);

    QHeaderView *vh;

    vh = ui->tbSave->verticalHeader();
    connect(vh, SIGNAL(sectionClicked(int)), this, SLOT(VHeaderClicked(int)));
}

void SendSave::VHeaderClicked(int index)
{
    QByteArray buf;
    QString value;
    QString endline;
    QTableWidgetItem *item;

    if (index >= ui->tbSave->rowCount() || index < 0)
        return;

    item = ui->tbSave->item(index, 1);
    value = item->text();
    item = ui->tbSave->item(index, 2);
    endline = item->text();

    dataMake(buf, value, endline);
    if (buf.size())
    {
        emit outData(buf);
    }
}

void SendSave::tableAddRow(QString &name, QString &type, QString &value, QString &endline)
{
    int row;

    row = ui->tbSave->rowCount();
    ui->tbSave->insertRow(row);
    QTableWidgetItem *item = new QTableWidgetItem[3];

    item->setText(name);
    ui->tbSave->setItem(row, 0, item);
    item ++;

    item->setText(value);
    ui->tbSave->setItem(row, 1, item);
    item ++;

    item->setText(endline);
    ui->tbSave->setItem(row, 2, item);

    setBtName(row, name);
}

void SendSave::on_send1_clicked()
{
    VHeaderClicked(0);
    hide();
}

void SendSave::on_send2_clicked()
{
    VHeaderClicked(1);
    hide();
}

void SendSave::on_send3_clicked()
{
    VHeaderClicked(2);
    hide();
}

void SendSave::on_add_clicked()
{
    QString sn;
    QString type = "ascii";
    QString endline = "\\n";
    QString value = "test";

    sn.sprintf("%d", ui->tbSave->rowCount() + 1);
    tableAddRow(sn, type, value, endline);
    worker->dbAddRow(sn, sn, type, value, endline);
}

void SendSave::on_tbSave_itemChanged(QTableWidgetItem *item)
{
    QString sn;
    QString val;

    sn.sprintf("%d", item->row() + 1);
    val = item->text();
    worker->dbUpdateRow(sn, item->column(), val);

    if (item->column() == 0)
    {
        setBtName(item->row(), val);
    }
}

void SendSave::setBtName(int row, QString name)
{
    if (row > 2)
        return;

    switch (row)
    {
    case 0:
        ui->send1->setText(name);
        break;
    case 1:
        ui->send2->setText(name);
        break;
    case 2:
        ui->send3->setText(name);
        break;
    }
}

void SendSave::on_clear_clicked()
{
    int row = ui->tbSave->rowCount();

    worker->dbDelAll();

    for (int i = 0; i < row; i ++)
    {
        ui->tbSave->removeRow(0);
    }
}

void SendSave::dataMake(QByteArray &buf, QString &value, QString &endline)
{
    if (value.isEmpty())
        return;

    buf = value.toStdString().c_str();
    int r, n;
    r = endline.count("\\r");
    n = endline.count("\\n");

    for (int i = 0; i < r; i++)
    {
        buf.append('\r');
    }

    for (int i = 0; i < n; i++)
    {
        buf.append('\n');
    }
}

void SendSave::on_send_clicked()
{
    int sel = ui->tbSave->currentRow();

    VHeaderClicked(sel);
}

QToolButton* SendSave::toolButton(int index)
{
    QToolButton* bt = NULL;

    switch (index)
    {
    case 0:
        bt = ui->send1;
        break;
    case 1:
        bt = ui->send2;
        break;
    case 2:
        bt = ui->send3;
        break;
    }

    return bt;
}
