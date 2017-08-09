#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QVariant>
#include <QDockWidget>

#define VERSION    "1.0.0"

#include "NewSession/NewSession.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->dockWidget->setWidget(ui->twProject);

    loadSession();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadSession()
{
    SesList sl;

    prjfile.Load("qstprj.xml");
    prjfile.GetSessionList(sl);

    for (int i = 0; i < sl.count(); i ++)
    {
        Session s;

        s = sl.at(i);
        addSession(s, false);
    }
}

void MainWindow::about(void)
{
    QMessageBox mbox;

    mbox.about(this, tr("关于"), tr("版本号: " VERSION));
}

void MainWindow::on_new_s_triggered()
{
    NewSession *ns = new NewSession;

    ns->show();
    ns->exec();

    if (ns->result() == 1)
    {
        Session set;

        ns->getSetting(set);

        addSession(set);
    }

    delete ns;
}

void MainWindow::addSession(Session &set, bool save)
{
    QTreeWidgetItem *child;

    child = addSessionProject(set);

    addSessionWindow(set, child);

    if (save)
    {
        prjfile.AddSession(set);
        prjfile.Save();
    }

    int cnt = dwlist.count();
    if (cnt > 1)
    {
        QDockWidget *f, *s;

        f = dwlist.at(cnt - 2);
        s = dwlist.at(cnt - 1);
        tabifyDockWidget(f, s);
    }
}

QTreeWidgetItem* MainWindow::addSessionProject(Session &set)
{
    QTreeWidgetItem *type = new QTreeWidgetItem;
    bool addtype = true;

    for (int i = 0; i < ui->twProject->topLevelItemCount(); i ++)
    {
        QTreeWidgetItem *tmptype = ui->twProject->topLevelItem(i);

        if (tmptype->text(0) == set.type)
        {
            delete type;
            type = tmptype;
            addtype = false;
            break;
        }
    }

    type->setText(0, set.type);
    if (addtype)
    {
        QVariant var(0);

        type->setData(0, Qt::UserRole, var);
        ui->twProject->addTopLevelItem(type);
    }

    QTreeWidgetItem *child = new QTreeWidgetItem;
    child->setText(0, set.name);
    type->addChild(child);

    return child;
}

#include "Serial/SerialTerm.h"
#include "Telnet/TelnetTerm.h"

bool MainWindow::addSessionWindow(Session &set, QTreeWidgetItem *item)
{
    QDockWidget *dock;
    QVariant var;
    bool add = false;

    dock= new QDockWidget(set.name, this);
    dock->setAllowedAreas(Qt::RightDockWidgetArea);

    var.setValue(dock);

    if (set.type == "串口终端")
    {
        item->setData(0, Qt::UserRole, var);

        SerialTerm *term = new SerialTerm;
        term->setSettings(set.param, set.id);

        dock->setWidget(term);
        add = true;
    }

    if (set.type == "telnet")
    {
        item->setData(0, Qt::UserRole, var);

        TelnetTerm *term = new TelnetTerm;
        term->setSettings(set.param);

        dock->setWidget(term);
        add = true;
    }

    if (add)
    {
        dwlist.append(dock);
        addDockWidget(Qt::RightDockWidgetArea, dock);
    }
    else
    {
        delete dock;
    }

    return add;
}

void MainWindow::on_twProject_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    QDockWidget *dock;
    QVariant var;

    var = item->data(column, Qt::UserRole);
    if (var == 0)
        return;

    dock = var.value<QDockWidget*>();

    dock->show();
    dock->raise();
}

void MainWindow::on_twProject_customContextMenuRequested(const QPoint &pos)
{
    QTreeWidgetItem* curItem;

    curItem = ui->twProject->itemAt(pos);
    if (curItem == NULL)
        return;

    QVariant var = curItem->data(0, Qt::UserRole);
    if (var == 0)
        return;

    QMenu *popMenu =new QMenu(this);

    popMenu->addAction(ui->del_s);//往菜单内添加QAction   该action在前面用设计器定义了
    popMenu->exec(QCursor::pos());

    delete popMenu;
}
