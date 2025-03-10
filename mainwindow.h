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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "session.h"
//#include "helpers/serialsettingshelper.h"

#include <QFile>
#include <QMainWindow>
#include <QSerialPort>
#include <QTextStream>
#include <QDateTime>
#include "console.h"

//#define PRG_NAME        "oled_demo"
//#define PRG_VERSION     "1.1"

//#define NUMFLAKES 10
//#define XPOS 0
//#define YPOS 1
//#define DELTAY 2

//#define LOGO16_GLCD_HEIGHT 16
//#define LOGO16_GLCD_WIDTH  16

QT_BEGIN_NAMESPACE

class QLabel;

namespace Ui {
class MainWindow;
}

QT_END_NAMESPACE

class Console;
class SettingsDialog;
class SettingsNetworkDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openSerialPort();
    void closeSerialPort();
    void about();
    void writeData_console(const QByteArray &data);
    void readData_serial();
    void saveSettings_serial();
    void loadSettings_serial();
    void saveSettings_network();
    void loadSettings_network();
    void saveSession();    
    void loadSession();
    void clear();

    void handleError_serial(QSerialPort::SerialPortError error);

    void process_ActionConfigure();
    void process_ActionConfigureNetwork();
    void process_ActionClear();
    void process_OpenSerialPort();
    void process_CloseSerialPort();
    void process_Close();
    void process_About();
    void process_AboutQt();

    void on_SettingsDialogApply();
    void on_NetworkSettingsDialogApply();

public slots:
    void onNetworkConnected();
    void onNetworkDisconnected();
    void onNoNetwork();

private:
    void initActionsConnections();
    void showStatusMessage(const QString &message);

private:
    Ui::MainWindow *m_ui = nullptr;
    QLabel *m_status = nullptr;
    Console *_console = nullptr;
    SettingsDialog* _settingsDialog = nullptr;
    SettingsNetworkDialog* _networkSettingsDialog = nullptr;

    void SetSettingsDialog_Serial();
    void SetSettingsDialog_Network();

public:    
    void setLocalEcho(bool v){_console->setLocalEcho(v);};
    void setStatusBarText(const QString& v);
};

#endif // MAINWINDOW_H
