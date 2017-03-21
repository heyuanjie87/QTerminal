#ifndef SERIALSETTING_H
#define SERIALSETTING_H

#include "Setting.h"

namespace Ui {
class SerialSetting;
}

class SerialSetting : public Setting
{
    Q_OBJECT

public:
    explicit SerialSetting(QWidget *parent = 0);
    ~SerialSetting();

    void getSetting(SessionSetting &ns);

private:
    Ui::SerialSetting *ui;
};

#endif // SERIALSETTING_H
