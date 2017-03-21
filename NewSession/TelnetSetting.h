#ifndef TELNETSETTING_H
#define TELNETSETTING_H

#include "Setting.h"

namespace Ui {
class TelnetSetting;
}

class TelnetSetting : public Setting
{
    Q_OBJECT

public:
    explicit TelnetSetting(QWidget *parent = 0);
    ~TelnetSetting();

    void getSetting(SessionSetting &ns);

private:
    Ui::TelnetSetting *ui;
};

#endif // TELNETSETTING_H
