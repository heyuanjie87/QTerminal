#ifndef NETASSIST_H
#define NETASSIST_H

#include <QMainWindow>
#include "NewSession/nstypes.h"

namespace Ui {
class NetAssist;
}

class QUdpSocket;
class SendSave;

class NetAssist : public QMainWindow
{
    Q_OBJECT

public:
    explicit NetAssist(QWidget *parent = 0);
    ~NetAssist();

    void setSettings(Session &ss);

private slots:
    void on_open_clicked();

private slots:
    void recordSend(QByteArray buf);
    void udpServerReadData();

    void on_rcvclear_clicked();

    void on_btsend_clicked();

private:
    void initSendSave();
    void initNet(Session &ss);
    void udpSend(QByteArray &buf);

private:
    Ui::NetAssist *ui;
    SendSave *dlgSS;
    QUdpSocket *udpServer;
    Session netParam;
    int protoType;
};

#endif // NETASSIST_H
