#ifndef NEWSESSION_H
#define NEWSESSION_H

#include <QDialog>
#include <QMap>
#include <QListWidgetItem>

#include "Setting.h"

namespace Ui {
class NewSession;
}

class NewSession : public QDialog
{
    Q_OBJECT

public:
    explicit NewSession(QWidget *parent = 0);
    ~NewSession();

    void getSetting(SessionSetting &s);

private slots:
    void on_sesType_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

private:
    Ui::NewSession *ui;
    SessionSetting nss;
    QMap <QString, Setting*> wSetting;
};

#endif // NEWSESSION_H
