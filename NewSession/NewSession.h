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

    void getSetting(Session &s);

private:
    void makeID(QString &id);

private slots:
    void on_sesType_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

private:
    Ui::NewSession *ui;
    QMap <QString, Setting*> wSetting;
};

#endif // NEWSESSION_H
