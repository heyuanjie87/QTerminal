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

    void setSettings(SessionSetting &ss);

private slots:
    void readData(const QString &data);
    void writeData(const QByteArray &data);

private slots:
    void on_btConnect_clicked();

private:
    void initTelnet();
    void initTerm();

private:
    Ui::TelnetTerm *ui;
    QTermWidget *term;
    SessionSetting settings;
    QtTelnet *telnet;
};

#endif // TELNETTERM_H
