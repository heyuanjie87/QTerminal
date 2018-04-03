#include "QKconfig.h"

void fixup_rootmenu(struct menu *menu, int *menu_cnt)
{
    struct menu *child;

    *menu_cnt ++;
    menu->flags |= MENU_ROOT;
    for (child = menu->list; child; child = child->next)
    {
        if (child->prompt && child->prompt->type == P_MENU)
        {
            fixup_rootmenu(child, menu_cnt);
        }
        else if (!menu_cnt)
            fixup_rootmenu(child, menu_cnt);
    }

    *menu_cnt --;
}

static void msgRecv_cb(struct msg_out *mo, int type, const char *fmt, va_list ap)
{
    QKconfig *c = (QKconfig *)mo->obj;
    QString str;

    str = str.vsprintf(fmt, ap);
    emit c->msgOut(str);
}

QKconfig::QKconfig(QObject *parent) : QObject(parent)
{
    memset(&kcm, 0, sizeof(kcm));

    moveToThread(&worker);

    connect(this, SIGNAL(parseReq(QString)), this, SLOT(parseDo(QString)),
            Qt::QueuedConnection);

    worker.start();

    kcm.msgout.print = msgRecv_cb;
    kcm.msgout.obj = this;
}

void QKconfig::parseDo(QString name)
{
    int err;

    err = conf_parse(name.toStdString().c_str(), &kcm);

    conf_read(NULL, &kcm);

    emit parseDone(err);
}

kcmenu_t* QKconfig::getMenu()
{
    return &kcm;
}

bool QKconfig::writeConfig(QString name)
{
    return conf_write(name.toStdString().c_str(), &kcm) == 0;
}

void QKconfig::putEnv(QString &env)
{
    QStringList list;

    list = env.split(",");
    for (int i = 0; i < list.size(); i ++)
    {
        putenv(list.at(i).toStdString().c_str());
    }
}

bool QKconfig::isChanged()
{
    return conf_get_changed(&kcm);
}
