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
#include "console.h"
#include "settingsdialog.h"
#include "enumhelper.h"

#include <QDateTime>
#include <QFileDialog>
#include <QLabel>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow),
    m_status(new QLabel),
    m_console(new Console),
    m_settings(new SettingsDialog),
    m_serial(new QSerialPort(this))
{
    m_ui->setupUi(this);
    m_ui->mainToolBar->setIconSize(QSize(80, 80));
    m_console->setEnabled(false);
    setCentralWidget(m_console);

    m_ui->actionConnect->setEnabled(true);
    m_ui->actionDisconnect->setEnabled(false);
    m_ui->actionQuit->setEnabled(true);
    m_ui->actionConfigure->setEnabled(true);
    //m_ui->actionSave->setEnabled(true);
    //m_ui->actionLoad->setEnabled(true);

    initActionsConnections();

    connect(m_serial, &QSerialPort::errorOccurred, this, &MainWindow::handleError);
    connect(m_serial, &QSerialPort::readyRead, this, &MainWindow::readData);
    connect(m_console, &Console::getData, this, &MainWindow::writeData);
    loadSettings();
}

MainWindow::~MainWindow()
{
    delete m_settings;
    delete m_ui;
}

void MainWindow::openSerialPort()
{
    const SettingsDialog::Settings p = m_settings->settings();
    m_serial->setPortName(p.name);
    m_serial->setBaudRate(p.baudRate);
    m_serial->setDataBits(p.dataBits);
    m_serial->setParity(p.parity);
    m_serial->setStopBits(p.stopBits);
    m_serial->setFlowControl(p.flowControl);
    if (m_serial->open(QIODevice::ReadWrite)) {
        m_console->setEnabled(true);
        m_console->setLocalEchoEnabled(p.localEchoEnabled);
        m_ui->actionConnect->setEnabled(false);
        m_ui->actionDisconnect->setEnabled(true);
        m_ui->actionConfigure->setEnabled(false);
        showStatusMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
                          .arg(p.name).arg(p.stringBaudRate).arg(p.stringDataBits)
                          .arg(p.stringParity).arg(p.stringStopBits).arg(p.stringFlowControl));
    } else {
        QMessageBox::critical(this, tr("Error"), m_serial->errorString());

        showStatusMessage(tr("Open error"));
    }

    //logd = new QList<struct logData>();
    logd.clear();
}

void MainWindow::closeSerialPort()
{
    if (m_serial->isOpen())
        m_serial->close();
    m_console->setEnabled(false);
    m_ui->actionConnect->setEnabled(true);
    m_ui->actionDisconnect->setEnabled(false);
    m_ui->actionConfigure->setEnabled(true);
    showStatusMessage(tr("Disconnected"));
    //logd.clear();
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Simple Terminal"),
                       tr("The <b>Simple Terminal</b> example demonstrates how to "
                          "use the Qt Serial Port module in modern GUI applications "
                          "using Qt, with a menu bar, toolbars, and a status bar."));
}

void MainWindow::writeData(const QByteArray &data)
{
    m_serial->write(data);

    logd.push_back(logData{QDateTime::currentDateTime(), 1, data });

}

void MainWindow::readData()
{
    const QByteArray data = m_serial->readAll();
    m_console->putData(data);
    logd.push_back(logData{QDateTime::currentDateTime(), 2, data });
}

void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), m_serial->errorString());
        closeSerialPort();
    }
}

void MainWindow::saveSession()
{

    logfn = QFileDialog::getSaveFileName(this, tr("Save File"), "/home/pi/terminal_logs", tr(""));
    if(logfn.isNull() || logfn.isEmpty()) return;
    QFile logf(logfn);
    logf.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
    //logts = new QTextStream(logf);

    QTextStream logts(&logf);
    logts<<"Port name; Baud rate; Data bits; Parity bits; Stop bits; Flow control\n";
    //QString baudRate = EnumHelper::ToString(m_serial->baudRate());
    logts<<m_serial->portName()<<";"
           << QString::number(m_serial->baudRate())<<";"
           << EnumHelper::ToString(m_serial->dataBits())<<";"
           << EnumHelper::ToString(m_serial->parity())<<";"
           << EnumHelper::ToString(m_serial->stopBits())<<";"
           << EnumHelper::ToString(m_serial->flowControl())<<"\n";
    // *logts<<m_serial->portName()<<";"
    //        << EnumHelper::getBaudRate(m_serial->baudRate())<<";"
    //        << EnumHelper::getDataBits(m_serial->dataBits())<<";"
    //        << EnumHelper::getParity(m_serial->parity())<<";"
    //        << EnumHelper::getStopBits(m_serial->stopBits())<<";"
    //        << EnumHelper::getFlowControl(m_serial->flowControl())<<"\n";
    for(int i = 0; i < logd.length(); i++){
        auto s = logd.at(i).wr==1?"TX":"RX";
        logts<<logd.at(i).timestamp.toString("yyyy.mm.dd@HH.mm.ss")<<" "<<s<<" "<<logd.at(i).data<<"\n";
    }
    QFile logf2(logfn+".txt");
    logf2.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
    logts.setDevice(&logf2);
    logts<<m_console->toPlainText();
    logf.close();
    logf2.close();
    saveSettings();
}

// void MainWindow::loadSession()
// {
//     settingsFn = QFileDialog::getOpenFileName(this, tr("Load Setting"), "/home/pi/terminal_settings", tr(""));
//     loadSettings();
// }

void MainWindow::clear()
{
    //if(!logd) return;
    logd.clear();
}

void MainWindow::initActionsConnections()
{
    connect(m_ui->actionConnect, &QAction::triggered, this, &MainWindow::openSerialPort);
    connect(m_ui->actionDisconnect, &QAction::triggered, this, &MainWindow::closeSerialPort);
    connect(m_ui->actionQuit, &QAction::triggered, this, &MainWindow::close);
    connect(m_ui->actionConfigure, &QAction::triggered, m_settings, &SettingsDialog::show);
    connect(m_ui->actionClear, &QAction::triggered, m_console, &Console::clear);
    connect(m_ui->actionClear, &QAction::triggered, this, &MainWindow::clear);
    connect(m_ui->actionAbout, &QAction::triggered, this, &MainWindow::about);
    connect(m_ui->actionAboutQt, &QAction::triggered, qApp, &QApplication::aboutQt);
    //connect(m_ui->actionSave, &QAction::triggered, this, &MainWindow::saveSession);
    //connect(m_ui->actionLoad, &QAction::triggered, this, &MainWindow::loadSession);
}

void MainWindow::showStatusMessage(const QString &message)
{
    m_status->setText(message);
}

void MainWindow::loadSettings()
{
    if(settingsFn.isNull() || settingsFn.isEmpty()){
        QDir d("/home/pi/terminal_settings");
        auto list = d.entryList(QDir::NoFilter, QDir::Time);
        if(list.isEmpty()) return;

        settingsFn = list.at(1);
        if(settingsFn.isNull() || settingsFn.isEmpty()) return;
        settingsFn = "/home/pi/terminal_settings/" + settingsFn;

    }
    QSettings settings(settingsFn, QSettings::NativeFormat);
    m_serial->setPortName(settings.value("name").toString());
    m_serial->setBaudRate(settings.value("bR").toInt());
    m_serial->setDataBits(settings.value("dB").value<QSerialPort::DataBits>());
    m_serial->setStopBits(settings.value("sB").value<QSerialPort::StopBits>());
    m_serial->setParity(settings.value("par").value<QSerialPort::Parity>());
    m_serial->setFlowControl(settings.value("fC").value<QSerialPort::FlowControl>());

    SettingsDialog::Settings p;
    p.name = m_serial->portName();

    qint32 baudRate_int = m_serial->baudRate();
    QSerialPort::BaudRate baudRate = static_cast<QSerialPort::BaudRate>(baudRate_int);
    p.baudRate = baudRate;

    p.dataBits = m_serial->dataBits();
    p.parity = m_serial->parity();
    p.stopBits = m_serial->stopBits();
    p.flowControl = m_serial->flowControl();
    p.localEchoEnabled = false;
    m_settings->setSettings(p);
}

void MainWindow::saveSettings()
{
    settingsFn = "/home/pi/terminal_settings/" + logfn.split('/').last();
    QSettings settings(settingsFn, QSettings::NativeFormat);
    QString name = m_serial->portName();
    qint32 bR = m_serial->baudRate();
    QSerialPort::DataBits dB = m_serial->dataBits();
    QSerialPort::StopBits sB = m_serial->stopBits();
    QSerialPort::Parity par = m_serial->parity();
    QSerialPort::FlowControl fC = m_serial->flowControl();
    settings.setValue("bR", bR);
    settings.setValue("dB", dB);
    settings.setValue("sB", sB);
    settings.setValue("par", par);
    settings.setValue("fC", fC);
    settings.setValue("name", name);
}
