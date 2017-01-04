#include "Ymodem.h"
#include "Modem.h"
#include "crc.h"

#include <QFile>
#include <QFileInfo>
#include <time.h>

Ymodem::Ymodem(Modem *parent)
{
    Stage = msFirst;
    sn = 0;
    isrun = false;
    ui = parent;
}

void Ymodem::close()
{
    isrun = false;
    if (!isFinished())
    {
        wait();
    }
}

void Ymodem::time_start()
{
    stx_time = time(NULL);
}

float Ymodem::speed_clc(int total, int remain)
{
   float s = 0;
   int t;

   t = (int)(time(NULL) - stx_time);
   s = (total - remain)/(float)t;

   return s;
}

void Ymodem::put(const QByteArray &data)
{
    msgq_push(data.at(0));
}

int Ymodem::makeFirstRsp(string &name, int size, QByteArray &byte)
{
    int len = 133;
    ymhead_t *pkt;
    uint16_t *sum;

    byte.resize(len);
    sn = 0;
    pkt = (ymhead_t*)byte.data();
    pkt->start = 0x01;
    pkt->sn = 0;
    pkt->nsn = 0xFF;
    memset(pkt->data, 0, sizeof(pkt->data));
    strcpy(pkt->data, name.c_str());
    sprintf(&pkt->data[name.size() + 1], "%d", size);

    sum = (uint16_t*)(((char*)pkt) + 131);
    *sum = crc16(pkt->data, 128);

    return len;
}

int Ymodem::makeNextRsp(char *data, int size, QByteArray &byte)
{
    int len = 0;
    ymhead_t *pkt;
    uint16_t *sum;

    byte.resize(3 + 1024 + 2);
    pkt = (ymhead_t *)byte.data();
    sn ++;
    pkt->start = 0x02;
    pkt->sn = sn;
    pkt->nsn = 0xFF - sn;
    memcpy(pkt->data, data, size);
    if (size < 1024)
    {
        memset(&pkt->data[size], 0, 1024 - size);
    }
    len = 1024 + 3;
    sum = (uint16_t*)(((char*)pkt) + len);
    *sum = crc16(pkt->data, 1024);
    len += 2;

    return len;
}

uint16_t Ymodem::crc16(char *data, int size)
{
    uint16_t sum;

    sum = crc16_ccitt(0, (uint8_t*)data, size);
    sum = ((sum >> 8) | (sum << 8));

    return sum;
}

void Ymodem::msgq_push(int msg)
{
    msgq.push(msg);
}

bool Ymodem::msgq_get(int &msg)
{
    if (msgq.empty())
        return false;

    msg = msgq.front();
    msgq.pop();

    return true;
}

int Ymodem::makeFinishRsp(QByteArray &byte)
{
    int len = 133;
    ymhead_t *pkt;
    uint16_t *sum;

    byte.resize(len);

    pkt = (ymhead_t*)byte.data();
    pkt->start = 0x01;
    pkt->sn = 0;
    pkt->nsn = 0xFF;
    memset(pkt->data, 0, sizeof(pkt->data));

    sum = (uint16_t*)(byte.data() + 131);
    *sum = crc16(pkt->data, 128);

    return len;
}

int Ymodem::makeEotRsp(QByteArray &byte)
{
   byte.resize(1);

   byte[0] = mcEOT;

   return 1;
}

void Ymodem::outData(const QByteArray &data)
{
    emit ui->outData(data);
}

void Ymodem::showStatus(const char *s)
{
    ui->showStatus(s);
}

void Ymodem::run()
{
    QString filename;
    char fbuf[1024];
    bool isread = false;
    QByteArray byte;
    int filesize = 0;
    QFile file;
    string stext;
    int remain = 0;

    showStatus("已启动Ymodem");
    ui->getFile(filename);
    if (filename.isEmpty())
    {
       showStatus("错误:文件名为空");
       goto err;
    }

    file.setFileName(filename);
    if (!file.open(QFile::ReadOnly))
    {
        showStatus("错误:打开文件失败");
        goto err;
    }

    msgq_push(mcREQ);

    isrun = true;
    while (isrun)
    {
        int msg = 0;

        msgq_get(msg);

        switch (Stage)
        {
        case msFirst:
        {
            switch (msg)
            {
            case mcREQ:
            {
                QFileInfo info(filename);

                showStatus("第一次传输请求");
                stext = info.fileName().toStdString();
                remain = file.size();
                filesize = remain;
                makeFirstRsp(stext, remain, byte);
                outData(byte);
            }
            break;
            case mcACK:
            {
                Stage = msReady;
            }
            break;
            }
        }
        break;
        case msReady:
        {
            switch (msg)
            {
            case mcREQ:
            {
                showStatus("第二次传输请求");
                Stage = msTrans;
                time_start();
            }
            break;
            }
        }
        break;
        case msTrans:
        {
            if (!isread)
            {
                int size;

                size = file.read(fbuf, 1024);
                remain -= size;
                makeNextRsp(fbuf, size, byte);

                isread = true;
                outData(byte);
            }

            switch (msg)
            {
            case mcACK:
                float speed;

                isread = false;
                speed = speed_clc(filesize, remain);
                emit showTransfer(filesize, remain, speed);
                if (remain == 0)
                {
                    Stage = msEnding;
                    msgq_push(mcACK);
                }
                break;
            }
        }
        break;
        case msRepeat:
        {
            outData(byte);
        }
        break;
        case msEnding:
        {
            switch (msg)
            {
            case mcACK:
                makeEotRsp(byte);
                outData(byte);
                Stage = msFinish;
                break;
            }
        }
        break;
        case msFinish:
        {
            switch (msg)
            {
            case mcACK:
                makeFinishRsp(byte);
                outData(byte);
                goto err;
                break;
            case mcNAK:
                makeEotRsp(byte);
                outData(byte);
                break;
            }
        }
        break;
        default:
            break;
        }

        msleep(10);
    }

err:
    showStatus("退出Ymodem");
}
