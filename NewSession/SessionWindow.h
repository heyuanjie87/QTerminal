#ifndef SESSIONWINDOW_H
#define SESSIONWINDOW_H

#include <QWidget>

#include "Setting.h"

class SessionWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SessionWindow();

    virtual QWidget* getWindow() = 0;
    virtual void setSetting(const SesParam &ns) = 0;
    virtual void open() = 0;
    virtual void close() = 0;

};

#endif // SESSIONWINDOW_H
