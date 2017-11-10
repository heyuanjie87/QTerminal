#include "Console.h"
#include "ui_console.h"

#include "QTermWidget/QTermWidget.h"
#include <QProcess>
#include <QDir>

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
        QString str;
        QStringList args;

        if (data == "\r\n")
        {
            term->putData(prompt);
            return;
        }

        str = data.left(data.size() - 2);

        if (data.left(2) == "cd")
        {
            QDir dir;
            QString path;

            path = str.right(str.size() - 3);
            if (dir.setCurrent(path))
            {
                prompt = "\n";
                prompt += path.toLocal8Bit() + ">";
                term->putData(prompt);
            }
            return;
        }

        child = new QProcess(this);
        connect(child, SIGNAL(readyRead()), this, SLOT(readProcess()), Qt::QueuedConnection);
        connect(child, SIGNAL(finished(int)), this, SLOT(childExited(int)));

        args = str.split(' ');
        str = args.takeFirst();
        child->setProcessChannelMode(QProcess::MergedChannels);

        child->start(str, args,QIODevice::ReadWrite);
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
