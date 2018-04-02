#ifndef NSTYPES_H
#define NSTYPES_H

#include <QMap>
#include <QList>

typedef QMap<QString, QString> SesParam;

typedef struct
{
    QString type;
    QString name;
    QString id;
    QString show;

    SesParam param;
}Session;

typedef QList<Session> SesList;

#endif // NSTYPES_H
