#include "Console.h"
#include "ui_console.h"

#include "QTermWidget/QTermWidget.h"
#include <QProcess>

Console::Console(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Console)
{
    ui->setupUi(this);

    child = NULL;
    term = new QTermWidget;
    setCentralWidget(term);

    term->setSendLine(true);

    connect(term, SIGNAL(outData(QByteArray)), this, SLOT(readTerm(QByteArray)));

    prompt = "\nqmzd>";
    term->putData(prompt);
}

Console::~Console()
{
    delete ui;
}
#include <QThread>
void Console::readTerm(const QByteArray &data)
{
    if (child == NULL)
    {
        QString name;
        QStringList args;

        if (data == "\r\n")
        {
            term->putData(prompt);
            return;
        }

        child = new QProcess;
        connect(child, SIGNAL(readyRead()), this, SLOT(readProcess()), Qt::QueuedConnection);
        connect(child, SIGNAL(finished(int)), this, SLOT(childExited(int)));

        name = data.left(data.size() - 2);

        args = name.split(' ');
        name = args.takeFirst();
        child->setProcessChannelMode(QProcess::MergedChannels);

        child->start(name,args,QIODevice::ReadWrite);
        if (!child->waitForStarted())
        {
            delete child;
            child = NULL;
            term->insertPlainText("执行失败\n");
        }
    }
    else
    {
        child->write(data);
    }
}

void Console::childExited(int err)
{
    term->putData(prompt);
    term->setSendLine(true);

    child->close();
    delete child;
    child = NULL;
}

void Console::readProcess()
{
    QByteArray buf;

    buf = child->readAll();

    term->putData(buf);
}
