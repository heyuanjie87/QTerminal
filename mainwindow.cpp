/****************************************************************************
**
** Copyright (C) 2012 Denis Shienkov <denis.shienkov@gmail.com>
** Copyright (C) 2012 Laszlo Papp <lpapp@kde.org>
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtSerialPort module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "settingsdialog.h"
#include "SendSave/SendSave.h"
#include <QMimeData>
#include <QMessageBox>
#include <QLabel>
#include <QtSerialPort/QSerialPort>
#include <QTimer>
#include "Modem/Modem.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_modemEn(false)
{
    ui->setupUi(this);

    term = new QTermWidget(this);

    setCentralWidget(term);
    setAcceptDrops(true);

    serial = new QSerialPort(this);

    settings = new SettingsDialog;

    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);
    ui->actionQuit->setEnabled(true);
    ui->actionConfigure->setEnabled(true);

    status = new QLabel;
    ui->statusBar->addWidget(status);

    initActionsConnections();

    connect(serial, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
            this, &MainWindow::handleError);

    connect(serial, &QSerialPort::readyRead, this, &MainWindow::readData);
    connect(term, &term->outData, this, &MainWindow::writeData);

    dlgSS = new SendSave;
    statusBar()->addWidget(ui->toolButton);

    connect(dlgSS, &dlgSS->outData, this, &MainWindow::writeData);

    statusBar()->addWidget(dlgSS->toolButton(0));
    statusBar()->addWidget(dlgSS->toolButton(1));
    statusBar()->addWidget(dlgSS->toolButton(2));

    modem = new Modem(this);
    connect(modem, &modem->outData, this, &MainWindow::writeData);

    modemCheck = new QTimer;
    modemCheck->setSingleShot(true);
    connect(modemCheck, SIGNAL(timeout()), this, SLOT(startModem()));

    connect(modem, &modem->exitTransfer, this, &this->exitTransfer);
}

MainWindow::~MainWindow()
{
    delete settings;
    delete ui;
    delete dlgSS;
    delete modem;
}

void MainWindow::startModem()
{
    QString filename;

    modem->getFile(filename);

    if (filename.isEmpty())
    {
        showStatus(string("请拖入文件"));
    }
    else
    {
        m_modemEn = true;
        modem->startTransfer();
    }
}

void MainWindow::exitTransfer()
{
    m_modemEn = false;
    modem->hide();
}

void MainWindow::openSerialPort()
{
    SettingsDialog::Settings p = settings->settings();
    serial->setPortName(p.name);
    serial->setBaudRate(p.baudRate);
    serial->setDataBits(p.dataBits);
    serial->setParity(p.parity);
    serial->setStopBits(p.stopBits);
    serial->setFlowControl(p.flowControl);
    if (serial->open(QIODevice::ReadWrite))
    {
        ui->actionConnect->setEnabled(false);
        ui->actionDisconnect->setEnabled(true);
        ui->actionConfigure->setEnabled(false);
        showStatusMessage(tr("连接到 %1")
                          .arg(p.name));
    }
    else
    {
        showStatus(string("打开出错"));
    }
}

void MainWindow::dropEvent(QDropEvent *event)
{
    QList<QUrl> urls;

    urls = event->mimeData()->urls();
    if (urls.isEmpty())
       return;

    QString filename = urls.first().toLocalFile();
    modem->setFile(filename);

    emit showStatus(filename.toStdString());
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    //如果为文件，则支持拖放
    if (event->mimeData()->hasFormat("text/uri-list"))
        event->acceptProposedAction();
}

void MainWindow::showStatus(string s)
{
    QString qs;

    qs = qs.fromStdString(s);
    statusBar()->showMessage(qs, 2000);
}

void MainWindow::closeSerialPort()
{
    if (serial->isOpen())
        serial->close();

    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);
    ui->actionConfigure->setEnabled(true);
    showStatus(string("已断开"));
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("版本:1.0.2 作者:heyuanjie"),
                       tr("将文件拖入窗口，收到'C'后进入Ymodem模式"));
}

void MainWindow::writeData(const QByteArray &data)
{
    serial->write(data);
}

void MainWindow::readData()
{
    QByteArray data = serial->readAll();

    if (m_modemEn)
    {
        modem->putData(data);
    }
    else
    {
        modemCheck->stop();
        if (data.at(data.size()- 1) == 'C')
        {
            modemCheck->start(20);
        }

        term->putData(data);
    }

    QString tmp;

    for (int i = 0; i < data.size(); i ++)
    {
        QString ch;
        tmp += ch.sprintf("0x%02X, ", (uint8_t)data[i]);
    }
    //qDebug(tmp.toStdString().c_str());
}

void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError)
    {
        QMessageBox::critical(this, tr("Critical Error"), serial->errorString());
        closeSerialPort();
    }
}

void MainWindow::initActionsConnections()
{
    connect(ui->actionConnect, &QAction::triggered, this, &MainWindow::openSerialPort);
    connect(ui->actionDisconnect, &QAction::triggered, this, &MainWindow::closeSerialPort);
    connect(ui->actionQuit, &QAction::triggered, this, &MainWindow::close);
    connect(ui->actionConfigure, &QAction::triggered, settings, &MainWindow::show);
    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::about);
    connect(ui->actionAboutQt, &QAction::triggered, qApp, &QApplication::aboutQt);
}

void MainWindow::showStatusMessage(const QString &message)
{
    status->setText(message);
}

void MainWindow::on_toolButton_clicked()
{
    dlgSS->show();
}

void MainWindow::on_actionClear_triggered()
{
    term->clear();
}
