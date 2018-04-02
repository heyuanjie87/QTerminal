#ifndef SERIALTERM_H
#define SERIALTERM_H

#include <QMainWindow>
#include <QSerialPort>

namespace Ui {
class SerialTerm;
}

class QTermWidget;
class SendSave;

#include "NewSession/Setting.h"

class SerialTerm : public QMainWindow
{
    Q_OBJECT

public:
    explicit SerialTerm(QWidget *parent = 0);
    ~SerialTerm();

    void setSettings(SesParam &ss, QString id);

private slots:
    void writeData(const QByteArray &data);
    void readData();
    void error(QSerialPort::SerialPortError e);

private slots:
    void on_btConnect_clicked();

private:
    void initSendSave();
    void initSerial();
    void initTerm();
    bool openSerial();

private:
    Ui::SerialTerm *ui;
    QTermWidget *term;
    SendSave *dlgSS;
    QSerialPort *serial;
    SesParam settings;
};

#endif // SERIALTERM_H
