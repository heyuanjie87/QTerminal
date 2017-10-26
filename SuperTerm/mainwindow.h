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
#include "projectfile.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void addSession(Session &set, bool save = true);
    QTreeWidgetItem* addSessionProject(Session &set);
    bool addSessionWindow(Session &set, QTreeWidgetItem *item);
    void loadSession();

private slots:
    void about(void);

    void on_new_s_triggered();

    void on_twProject_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_twProject_customContextMenuRequested(const QPoint &pos);

    void on_del_s_triggered();

private:
    void menuInit(void);

private:
    Ui::MainWindow *ui;
    ProjectFile prjfile;
    QDockWidget *lastdock;
};

#endif // MAINWINDOW_H
