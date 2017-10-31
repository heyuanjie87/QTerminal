#ifndef CONSOLE_H
#define CONSOLE_H

#include <QMainWindow>

namespace Ui {
class Console;
}

class QTermWidget;
class QProcess;

class Console : public QMainWindow
{
    Q_OBJECT

public:
    explicit Console(QWidget *parent = 0);
    ~Console();

private slots:
    void readProcess();
    void readTerm(const QByteArray &data);
    void childExited(int err);

private:
    Ui::Console *ui;
    QTermWidget *term;
    QProcess *child;
    QByteArray prompt;
};

#endif // CONSOLE_H
