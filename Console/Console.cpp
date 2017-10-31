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
    term->setEcho(true);
    term->setSendLine(true);

    connect(term, SIGNAL(outData(QByteArray)), this, SLOT(readTerm(QByteArray)));

    prompt = "\nqmzd>";
    term->putData(prompt);
}

Console::~Console()
{
    delete ui;
}

void Console::readTerm(const QByteArray &data)
{
    if (child == NULL)
    {
        QString name;

        if (data == "\r\n")
        {
            term->putData(prompt);
            return;
        }

        child = new QProcess;
        connect(child, SIGNAL(readyRead()), this, SLOT(readProcess()));
        connect(child, SIGNAL(finished(int)), this, SLOT(childExited(int)));

        name = data;
        child->start(name);
        child->waitForStarted();
        term->setSendLine(false);
        term->setEcho(true);
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
