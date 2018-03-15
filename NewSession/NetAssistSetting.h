#ifndef NETASSISTSETTING_H
#define NETASSISTSETTING_H

#include "Setting.h"

namespace Ui {
class NetAssistSetting;
}

class NetAssistSetting : public Setting
{
    Q_OBJECT

public:
    explicit NetAssistSetting(QWidget *parent = 0);
    ~NetAssistSetting();

    void getSetting(SesParam &ns);

private:
    Ui::NetAssistSetting *ui;
};

#endif // NETASSISTSETTING_H
