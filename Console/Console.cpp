#include "Console.h"
#include "ui_console.h"

#include "QTermWidget/QTermWidget.h"
#include <QProcess>
#include <QDir>

#include "pty.h"

Console::Console(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Console),
    pty(NULL)
{
    ui->setupUi(this);

    term = new QTermWidget;
    setCentralWidget(term);

    connect(term, SIGNAL(outData(QByteArray)),
            this, SLOT(writePty(QByteArray)));
}

Console::~Console()
{
    delete ui;
    delete pty;
}

void Console::writePty(const QByteArray &data)
{
    if (pty)
    {
        pty->write(data);
    }
}

void Console::readPty()
{
    QByteArray buf;

    buf = pty->readAll();

    term->putData(buf);
}

void Console::setSettings(SesParam &parm, QString id)
{
    QString sh = getenv("ComSpec");

    startShell(sh);
}

void Console::startShell(QString fullpath, QString arg)
{
    if (pty == NULL)
    {
        pty = new Pty;

        connect(pty, SIGNAL(readyRead()),
                this, SLOT(readPty()));

        pty->start(fullpath, arg);
    }
}
