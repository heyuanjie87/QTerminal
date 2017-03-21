#ifndef SETTING_H
#define SETTING_H

#include <QWidget>
#include <QMap>

typedef QMap <QString, QString> SessionSetting;

class Setting : public QWidget
{
    Q_OBJECT
public:
    explicit Setting(QWidget *parent = 0);

    virtual void getSetting(SessionSetting &ns) = 0;

signals:

public slots:
};

#endif // SETTING_H
