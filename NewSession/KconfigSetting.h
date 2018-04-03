#ifndef KCONFIGSETTING_H
#define KCONFIGSETTING_H

#include "Setting.h"

namespace Ui {
class KconfigSetting;
}

class KconfigSetting : public Setting
{
    Q_OBJECT

public:
    explicit KconfigSetting(QWidget *parent = 0);
    ~KconfigSetting();

    void getSetting(SesParam &ns);

private slots:
    void on_find_clicked();

private:
    Ui::KconfigSetting *ui;
};

#endif // KCONFIGSETTING_H
