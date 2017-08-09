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

    void updateDevice();
    void getSetting(SesParam &ns);

private slots:
    void on_devname_activated(int index);

private:
    void initParam();

private:
    Ui::SerialSetting *ui;
};

#endif // SERIALSETTING_H
