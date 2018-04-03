#ifndef QKCONFIG_H
#define QKCONFIG_H

#include <QObject>
#include <QThread>
#include "lkc.h"

class QKconfig : public QObject
{
    Q_OBJECT

public:
    explicit QKconfig(QObject *parent = 0);

    kcmenu_t* getMenu();

    bool writeConfig(QString name = "");
    bool isChanged();
    void putEnv(QString &env);

signals:
    void parseReq(QString name);

signals:
    void parseDone(int err);
    void msgOut(QString str);

public slots:
    void parseDo(QString name);

private:
    QThread worker;
    kcmenu_t kcm;
};

#endif // QKCONFIG_H
