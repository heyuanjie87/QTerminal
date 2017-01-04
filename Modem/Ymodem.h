#ifndef YMODEM_H
#define YMODEM_H

#include <QThread>
#include <queue>
#include <QTime>
#include <time.h>

using namespace std;
class Modem;

class Ymodem : public QThread
{
    Q_OBJECT

public:
    Ymodem(Modem *parent);

    void close();
    void put(const QByteArray &data);

    int makeFirstRsp(string &name, int size, QByteArray &byte);
    int makeNextRsp(char *data, int size, QByteArray &byte);
    int makeEotRsp(QByteArray &byte);
    int makeFinishRsp(QByteArray &byte);

signals:
    void showTransfer(int total, int remain, float speed);

private:
    enum modemWaitfor
    {
        mwNon = 0x00,
        mwReq = 0x43,
        mwAck = 0x06,
    };

    enum modemStage
    {
        msFirst,
        msReady,
        msTrans,
        msRepeat,
        msEnding,
        msFinish,
    };

    enum modemCode
    {
        mcSOH = 0x01,
        mcSTX = 0x02,
        mcEOT = 0x04,
        mcACK = 0x06,
        mcNAK = 0x15,
        mcCAN = 0x18,
        mcREQ = 0x43,
    };

    typedef struct
    {
        uint8_t start;
        uint8_t sn;
        uint8_t nsn;
        char data[128];
        //short crc;
    }ymhead_t;

private:
    void run();
    void msgq_push(int msg);
    bool msgq_get(int &msg);
    uint16_t crc16(char *data, int size);
    void time_start();
    float speed_clc(int total, int remain);
    void outData(const QByteArray &data);
    void showStatus(const char *s);

private:
    enum modemStage Stage;
    enum modemWaitfor Wait;
    bool isrun;
    Modem *ui;
    uint8_t sn;
    queue <int> msgq;
    time_t  stx_time;
};

#endif // YMODEM_H
