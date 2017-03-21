#ifndef SERIALTERM_H
#define SERIALTERM_H

#include "NewSession/SessionWindow.h"
#include "QTermWidget/QTermWidget.h"

class QSerialPort;

class SerialTerm : public SessionWindow
{
    Q_OBJECT

public:
    explicit SerialTerm(QWidget *parent = 0);

    QWidget* getWindow();
    void setSetting(const SessionSetting &ss);
    void open();
    void close();

signals:

private slots:
    void readData();
    void writeData(const QByteArray &data);

private:
    QTermWidget *term;
    SessionSetting settings;
    QSerialPort *serial;
};

#endif // SERIALTERM_H
