#include "pty.h"
#include <QWinEventNotifier>

Pty::Pty(QObject *parent) : QObject(parent)
{
    wpty = NULL;
    memset(&rov, 0, sizeof(rov));
    connect(this, &_queRR, this, &pendRR,
            Qt::QueuedConnection);
}

Pty::~Pty()
{
    winpty_free(wpty);
}

bool Pty::start(QString name, QString args = "")
{
    std::wstring program, cmdline;

    program = name.toStdWString();
    cmdline = args.toStdWString();

    auto agentCfg = winpty_config_new(0, nullptr);

    wpty = winpty_open(agentCfg, nullptr);

    winpty_config_free(agentCfg);

    conin = CreateFileW(winpty_conin_name(wpty), GENERIC_WRITE,
                        0, nullptr, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, nullptr);
    conout = CreateFileW(winpty_conout_name(wpty), GENERIC_READ,
                         0, nullptr, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, nullptr);

    auto spawnCfg = winpty_spawn_config_new(
            WINPTY_SPAWN_FLAG_AUTO_SHUTDOWN,
            program.data(),
            cmdline.data(),
            nullptr, nullptr, nullptr);

    BOOL spawnSuccess = winpty_spawn(
        wpty, spawnCfg, nullptr, nullptr, nullptr, nullptr);

    inbuf.reserve(256);
    rov.Pointer = this;
    ReadFileEx(conout, inbuf.data(), 256, &rov, (LPOVERLAPPED_COMPLETION_ROUTINE)readFileComp);

    return (bool)spawnSuccess;
}

void Pty::readFileComp(DWORD err, DWORD len, OVERLAPPED *ov)
{
    Pty *self = (Pty*)ov->Pointer;

    self->rxsize = len;
    emit self->_queRR();
}

int Pty::write(const QByteArray &buf)
{
    DWORD len = 0;

    WriteFile(conin, buf.data(), buf.size(), &len, NULL);

    return len;
}

void Pty::pendRR()
{
    emit readyRead();
}

QByteArray Pty::readAll()
{
    QByteArray ret;

    ret.resize(rxsize);
    memcpy(ret.data(), inbuf.data(), rxsize);

    memset(&rov, 0, sizeof(rov));
    rov.Pointer = this;
    ReadFileEx(conout, inbuf.data(), 256, &rov, readFileComp);

    return ret;
}

