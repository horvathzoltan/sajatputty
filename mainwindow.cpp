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
#include "settingsnetworkdialog.h"

//#include "enumhelper.h"
//#include "enumhelper.h"
//#include "session.h"
#include "console.h"

#include <QDateTime>
#include <QFileDialog>
#include <QLabel>
#include <QMessageBox>

#include "infrastructure/globals.h"
#include <helpers/filenamehelper.h>

#include <helpers/serialsettingshelper.h>

extern Globals _globals;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow),
    m_status(new QLabel),    
    _settingsDialog(new SettingsDialog),
    _networkSettingsDialog(new SettingsNetworkDialog)

{
    m_ui->setupUi(this);
    m_ui->mainToolBar->setIconSize(QSize(48, 48));

    _console = new Console(this);
    _console->setEnabled(true);
    setCentralWidget(_console);

    //_console->setLayout(m_ui->tab_serial->layout());
    //_console->show();

    // QPlainTextEdit* _plt = new QPlainTextEdit(this);
    // setCentralWidget(_plt);
    // _plt->setReadOnly(true);
    // _plt->show();


    m_ui->actionConnect->setEnabled(true);
    m_ui->actionDisconnect->setEnabled(false);
    m_ui->actionQuit->setEnabled(true);
    m_ui->actionConfigure->setEnabled(true);

    initActionsConnections();

    connect(_globals.serial_ptr(), &QSerialPort::errorOccurred, this, &MainWindow::handleError_serial);
    connect(_globals.serial_ptr(), &QSerialPort::readyRead, this, &MainWindow::readData_serial);
    connect(_console, &Console::getData, this, &MainWindow::writeData_console);

    // settings apply
    connect(_settingsDialog, &SettingsDialog::apply, this, &MainWindow::on_SettingsDialogApply);
    // networkSettings apply
    connect(_networkSettingsDialog, &SettingsNetworkDialog::apply, this, &MainWindow::on_NetworkSettingsDialogApply);
}

/*
*
*/

void MainWindow::initActionsConnections()
{
    /*connection*/
    connect(m_ui->actionConnect, &QAction::triggered, this, &MainWindow::process_OpenSerialPort);
    connect(m_ui->actionDisconnect, &QAction::triggered, this, &MainWindow::process_CloseSerialPort);
    /*settings*/
    connect(m_ui->actionConfigure, &QAction::triggered, this, &MainWindow::process_ActionConfigure);
    connect(m_ui->actionLoadSettings, &QAction::triggered, this, &MainWindow::loadSettings_serial);
    connect(m_ui->actionSaveSettings, &QAction::triggered, this, &MainWindow::saveSettings_serial);
    /*session*/
    connect(m_ui->actionClear, &QAction::triggered, this, &MainWindow::process_ActionClear);
    connect(m_ui->actionSaveSession, &QAction::triggered, this, &MainWindow::saveSession);
    connect(m_ui->actionLoadSession, &QAction::triggered, this, &MainWindow::loadSession);
    /*help / about*/
    connect(m_ui->actionAbout, &QAction::triggered, this, &MainWindow::process_About);
    connect(m_ui->actionAboutQt, &QAction::triggered, this, &MainWindow::process_AboutQt);
    /*app*/
    connect(m_ui->actionQuit, &QAction::triggered, this, &MainWindow::process_Close);
    /*settings_network*/
    connect(m_ui->actionConfigure_Network, &QAction::triggered, this, &MainWindow::process_ActionConfigureNetwork);
    connect(m_ui->actionSaveSettings_Network, &QAction::triggered, this, &MainWindow::saveSettings_network);
    connect(m_ui->actionLoadSettings_Network, &QAction::triggered, this, &MainWindow::loadSettings_network);
}

void MainWindow::process_ActionConfigure()
{
    //_console->appendText("many many");

    SetSettingsDialog_Serial();
    _settingsDialog->show();
}

void MainWindow::process_ActionClear()
{
    _console->clear();
    clear();
}

void MainWindow::process_OpenSerialPort()
{
    openSerialPort();
}

void MainWindow::process_CloseSerialPort()
{
    closeSerialPort();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    process_Close();
}

void MainWindow::process_Close()
{    
    _settingsDialog->close();
    _networkSettingsDialog->close();
    close();
}

void MainWindow::process_About()
{
    about();
}

void MainWindow::process_AboutQt()
{
    QApplication::aboutQt();
}

void MainWindow::process_ActionConfigureNetwork()
{
    SetSettingsDialog_Network();
    _networkSettingsDialog->show();
}

/*
*
*/

void MainWindow::on_SettingsDialogApply()
{
    SerialSettingsVM p = _settingsDialog->settings();

    _globals._serialManager.setSettings(p);
    _console->setLocalEcho(p.localEchoEnabled);
    QString fn = FileNameHelper::serialSettingsFilePath();
    _globals._serialManager.saveSettings(fn, _console->localEcho());
}


MainWindow::~MainWindow()
{
    delete _settingsDialog;
    delete m_ui;
}


void MainWindow::about()
{
    QMessageBox::about(this, tr("About Simple Terminal"),
                       tr("The <b>Simple Terminal</b> example demonstrates how to "
                          "use the Qt Serial Port module in modern GUI applications "
                          "using Qt, with a menu bar, toolbars, and a status bar."));
}

void MainWindow::clear()
{
    _globals._sessionLog.clear();
    _console->clear();
}

// void MainWindow::showStatusMessage(const QString &message)
// {
//     m_status->setText(message);
// }


/**/

void MainWindow::saveSettings_serial()
{
    QString fd = FileNameHelper::custom_serialSettingsFilePath();
    QString fn = QFileDialog::getSaveFileName(this, "Save Setting", fd, "Ini file (*.ini)");
    _globals._serialManager.saveSettings(fn, _console->localEcho());
}

void MainWindow::loadSettings_serial()
{
    QString fd = FileNameHelper::terminalDirPath();
    auto fn  = QFileDialog::getOpenFileName(this, tr("Load Setting"), fd, "Ini file (*.ini)");
    if(fn.isEmpty()) return;

    bool localEcho;
    _globals._serialManager.loadSettings(fn, &localEcho);
    _console->setLocalEcho(localEcho);
}

/**/
void MainWindow::saveSettings_network()
{
    QString fd = FileNameHelper::custom_networkSettingsFilePath();
    QString fn = QFileDialog::getSaveFileName(this, "Save Network Setting", fd, "Ini file (*.ini)");
    _globals._networkManager.saveSettings(fn);
}

void MainWindow::loadSettings_network()
{
    QString fd = FileNameHelper::terminalDirPath();
    auto fn  = QFileDialog::getOpenFileName(this, tr("Load Network Setting"), fd, "Ini file (*.ini)");
    if(fn.isEmpty()) return;

    _globals._networkManager.loadSettings(fn);
}


void MainWindow::saveSession()
{
    QString fd = FileNameHelper::custom_logFilePath();
    auto fn = QFileDialog::getSaveFileName(this, tr("Save Session"), fd, "Log file (*.txt)");

    QString stxt = _globals._serialManager.MSerial_ToString(_console->localEcho()); //SerialSettingsHelper::MSerial_ToString(_serial, _console->localEcho());
    //QString ctxt = _console->toPlainText();
    _globals._sessionLog.saveSession(fn, stxt);
}

void MainWindow::loadSession()
{
    QString fd = FileNameHelper::terminalDirPath();
    auto fn  = QFileDialog::getOpenFileName(this, tr("Load Session"), fd, "Log file (*.txt)");
    if(fn.isEmpty()) return;

    QString stxt = _globals._sessionLog.loadSession(fn);
    _console->clear();
    _console->appendText(stxt);
}

void MainWindow::setStatusBarText(const QString &v)
{
    m_ui->statusBar->showMessage(v);
}

/**/

void MainWindow::onNetworkConnected()
{
    _globals._helpers._sysinfoHelper.InitNetwork();
    QString sysInfo = _globals._helpers._sysinfoHelper.Get_SysInfo();
    setStatusBarText(sysInfo + " connected");
}

void MainWindow::onNetworkDisconnected()
{
    //_globals._helpers._sysinfoHelper.InitNetwork();
    QString sysInfo = _globals._helpers._sysinfoHelper.Get_SysInfo();
    setStatusBarText(sysInfo + " disconnected");
}

void MainWindow::onNoNetwork()
{
    // ha nincs hálózat, megpróbáljuk keresni
    _globals._helpers._sysinfoHelper.InitNetwork();
    int nix = _globals._helpers._sysinfoHelper.networkInterfaceIx();
    bool ok = nix>0;
    QString msg = ok?"connected":"no network";
    if(ok)
    {
        _globals._networkMonitor.setInterfaceIndex(nix);
    }

    QString sysInfo = _globals._helpers._sysinfoHelper.Get_SysInfo();
    setStatusBarText(sysInfo + " "+ msg);
}

void MainWindow::SetSettingsDialog_Serial()
{
    SerialSettingsVM p = _globals._serialManager.getSettings();
    _settingsDialog->WriteSettings(p);
}

/*network_settings*/

void MainWindow::SetSettingsDialog_Network()
{
    NetworkSettingsVM p = _globals._networkManager.getSettings();
    _networkSettingsDialog->WriteSettings(p);
}

void MainWindow::on_NetworkSettingsDialogApply()
{
    NetworkSettingsVM p = _networkSettingsDialog->settings();
    _globals._networkManager.setSettings(p);
    QString fn = FileNameHelper::networkSettingsFilePath();
    _globals._networkManager.saveSettings(fn);
}


/*CONSOLE*/

void MainWindow::handleError_serial(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), _globals._serialManager.errorString());
        closeSerialPort();
    }
}

/*SERIALPORT*/

void MainWindow::openSerialPort(){
    bool ok = _globals._serialManager.openSerialPort();
    if(ok)
    {
        m_ui->actionConnect->setEnabled(false);
        m_ui->actionDisconnect->setEnabled(true);
        m_ui->actionConfigure->setEnabled(false);
        _console->setEnabled(true);
        QString msg = _globals._serialManager.MSerial_ToString(_console->localEcho()); //SerialSettingsHelper::MSerial_ToString(_globals._serial, _console->localEcho());
        //showStatusMessage("Connected:"+msg);
        _console->appendText("connected:"+msg);

        NetworkSettingsVM s = _globals._networkManager.getSettings();
        LogMode logMode = _globals._networkManager.logMode();
        _globals._tcpSender.Init(s.serverIp, s.serverPort, logMode);
    }
    else
    {
        QMessageBox::critical(this, tr("Error"), _globals._serialManager.errorString());
        //showStatusMessage(tr("Open error"));
    }
    _globals._sessionLog.clear();
}
// a serialsettingshelper beolvassa fájlból a m_serial-ba

void MainWindow::closeSerialPort()
{
    _globals._serialManager.closeSerialPort();
    _console->setEnabled(false);

    m_ui->actionConnect->setEnabled(true);
    m_ui->actionDisconnect->setEnabled(false);
    m_ui->actionConfigure->setEnabled(true);
    //showStatusMessage(tr("Disconnected"));

    _globals._tcpSender.Disconnect(),

    _console->appendText("disconnected");
}


void MainWindow::writeData_console(const QByteArray &data)
{
    SerialData d(SerialData::Type::TX, data);

    // amit beírunk a konzolba
    // ha van echo, kirakjuk a konzolra is
    if (_console->localEcho())
    {
        _console->appendData(d);
    }
    // kirakjuk a logba is
    _globals._sessionLog.append(d);
    // majd a portra is
    _globals._serialManager.writeData(d);
    // amit beírtunk, és van network, kiküldjük

    ChanelMode chanelMode = _globals._networkManager.chanelMode();
    if(chanelMode == ChanelMode::TX || chanelMode == ChanelMode::RXTX)
    {
        _globals._tcpSender.send(d);
    }
}

void MainWindow::readData_serial()
{
    const QByteArray data = _globals._serialManager.readAll();
    SerialData d(SerialData::Type::RX, data);

    // ami jött data
    // kirakjuk a konzolra
    _console->appendData(d);
    // kirakjuk a logba is

    _globals._sessionLog.append(d);
    // amit kiolvastunk, és van network, kiküldjük

    ChanelMode chanelMode = _globals._networkManager.chanelMode();
    if(chanelMode == ChanelMode::RX || chanelMode == ChanelMode::RXTX)
    {
        _globals._tcpSender.send(d);
    }
}
