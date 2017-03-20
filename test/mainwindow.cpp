#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "dialog.h"
#include "QTermWidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    test = new Dialog;
    term = new QTermWidget;

    setCentralWidget(term);

    connect(test, &test->outData, term, &term->putData);

    statusBar()->addWidget(ui->bttest);
    test->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_bttest_clicked()
{
    test->show();
    test->activateWindow();
}
