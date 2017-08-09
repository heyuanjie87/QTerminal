#ifndef SETTING_H
#define SETTING_H

#include <QWidget>
#include <QMap>

#include "nstypes.h"

class Setting : public QWidget
{
    Q_OBJECT
public:
    explicit Setting(QWidget *parent = 0);

    virtual void getSetting(SesParam &ns) = 0;

signals:

public slots:
};

#endif // SETTING_H
