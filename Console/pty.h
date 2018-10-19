#ifndef PTY_H
#define PTY_H

#include <QObject>
#include <QByteArray>
#include <synchapi.h>

#include "winpty.h"

class Pty : public QObject
{
    Q_OBJECT

public:
    explicit Pty(QObject *parent = 0);
    ~Pty();

    bool start(QString name, QString args);
    QByteArray readAll();
    int write(const QByteArray &buf);

signals:
    void readyRead();
    void _queRR();

private:
    static void __stdcall readFileComp(DWORD err, DWORD len, OVERLAPPED *ov);
    void pendRR();

private:
    winpty_t *wpty;
    HANDLE conin;
    HANDLE conout;
    HANDLE conerr;
    OVERLAPPED rov;
    QByteArray inbuf;
    DWORD rxsize;
};

#endif // PTY_H
