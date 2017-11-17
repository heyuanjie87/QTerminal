#ifndef CONSOLE_H
#define CONSOLE_H

#include <QMainWindow>

namespace Ui {
class Console;
}

class QTermWidget;
class QProcess;
class Pty;

#include "NewSession/Setting.h"

class Console : public QMainWindow
{
    Q_OBJECT

public:
    explicit Console(QWidget *parent = 0);
    ~Console();

    void setSettings(SesParam &parm, QString id);

private slots:
    void readPty();
    void writePty(const QByteArray &data);

private:
    void startShell(QString fullpath, QString arg = "");

private:
    Ui::Console *ui;
    QTermWidget *term;
    QProcess *child;
    Pty *pty;
};

#endif // CONSOLE_H
