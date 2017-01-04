#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class Dialog;
class QTermWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_bttest_clicked();

private:
    Ui::MainWindow *ui;
    Dialog *test;
    QTermWidget *term;
};

#endif // MAINWINDOW_H
