#ifndef TELNETTERM_H
#define TELNETTERM_H

#include <QMainWindow>

namespace Ui {
class TelnetTerm;
}

#include "NewSession/SessionWindow.h"
#include "QTermWidget/QTermWidget.h"

class QtTelnet;

class TelnetTerm : public QMainWindow
{
    Q_OBJECT

public:
    explicit TelnetTerm(QWidget *parent = 0);
    ~TelnetTerm();

private slots:
    void readData(QString &data);

private slots:
    void on_btConnect_clicked();

private:
    Ui::TelnetTerm *ui;
    QTermWidget *term;
    SessionSetting settings;
    QtTelnet *telnet;
};

#endif // TELNETTERM_H
