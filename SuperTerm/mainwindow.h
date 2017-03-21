#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QList>
#include <QDockWidget>

namespace Ui {
class MainWindow;
}

#include "NewSession/Setting.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void addSession(SessionSetting &set);
    QTreeWidgetItem* addSessionProject(SessionSetting &set);
    void addSessionWindow(SessionSetting &set, QTreeWidgetItem *item);

private slots:
    void about(void);

    void on_new_s_triggered();

private:
    void menuInit(void);

private:
    Ui::MainWindow *ui;
    QList <QDockWidget*> dwlist;
};

#endif // MAINWINDOW_H
