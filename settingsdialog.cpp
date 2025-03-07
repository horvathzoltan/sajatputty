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

#include "helpers/enumhelper.h"
#include "settingsdialog.h"
#include "ui_settingsdialog.h"

#include <QIntValidator>
#include <QLineEdit>
#include <QSerialPortInfo>
#include <QMetaEnum>

#include <helpers/serialsettingshelper.h>

static const char blankString[] = QT_TRANSLATE_NOOP("SettingsDialog", "N/A");

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::SettingsDialog),
    m_intValidator(new QIntValidator(0, 4000000, this))
{
    m_ui->setupUi(this);

    m_ui->baudRateBox->setInsertPolicy(QComboBox::NoInsert);

    connect(m_ui->applyButton, &QPushButton::clicked,
            this, &SettingsDialog::applyButtonClicked);
    connect(m_ui->serialPortInfoListBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &SettingsDialog::showPortInfo);
    connect(m_ui->baudRateBox,  QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &SettingsDialog::checkCustomBaudRatePolicy);
    connect(m_ui->serialPortInfoListBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &SettingsDialog::checkCustomDevicePathPolicy);

    fillPortsParameters();
    fillPortsInfo();
}

SettingsDialog::~SettingsDialog()
{
    delete m_ui;
}

void SettingsDialog::applyButtonClicked()
{
    ReadSettings();
    emit apply();
    hide();
}

void SettingsDialog::WriteSettings(const SettingsVM& p)
{
    _currentSettings = p;

    m_ui->serialPortInfoListBox->setCurrentText(p.portName);

    m_ui->baudRateBox->setCurrentText(SerialSettingsHelper::BaudToText(p.baudRate));
    m_ui->dataBitsBox->setCurrentText(SerialSettingsHelper::DataBitsToText(p.dataBits));
    m_ui->stopBitsBox->setCurrentText(SerialSettingsHelper::StopBitsToText(p.stopBits));
    m_ui->parityBox->setCurrentText(SerialSettingsHelper::ParityToText(p.parity));
    m_ui->flowControlBox->setCurrentText(SerialSettingsHelper::FlowControlToText(p.flowControl));
}

void SettingsDialog::showPortInfo(int idx)
{
    if (idx == -1)
        return;

    const QStringList list = m_ui->serialPortInfoListBox->itemData(idx).toStringList();
    m_ui->descriptionLabel->setText(tr("Description: %1").arg(list.count() > 1 ? list.at(1) : tr(blankString)));
    m_ui->manufacturerLabel->setText(tr("Manufacturer: %1").arg(list.count() > 2 ? list.at(2) : tr(blankString)));
    m_ui->serialNumberLabel->setText(tr("Serial number: %1").arg(list.count() > 3 ? list.at(3) : tr(blankString)));
    m_ui->locationLabel->setText(tr("Location: %1").arg(list.count() > 4 ? list.at(4) : tr(blankString)));
    m_ui->vidLabel->setText(tr("Vendor Identifier: %1").arg(list.count() > 5 ? list.at(5) : tr(blankString)));
    m_ui->pidLabel->setText(tr("Product Identifier: %1").arg(list.count() > 6 ? list.at(6) : tr(blankString)));
}



void SettingsDialog::checkCustomBaudRatePolicy(int idx)
{
    const bool isCustomBaudRate = !m_ui->baudRateBox->itemData(idx).isValid();
    m_ui->baudRateBox->setEditable(isCustomBaudRate);
    if (isCustomBaudRate) {
        m_ui->baudRateBox->clearEditText();
        QLineEdit *edit = m_ui->baudRateBox->lineEdit();
        edit->setValidator(m_intValidator);
    }
}

void SettingsDialog::checkCustomDevicePathPolicy(int idx)
{
    const bool isCustomPath = !m_ui->serialPortInfoListBox->itemData(idx).isValid();
    m_ui->serialPortInfoListBox->setEditable(isCustomPath);
    if (isCustomPath)
        m_ui->serialPortInfoListBox->clearEditText();
}





void SettingsDialog::fillPortsParameters()
{
    m_ui->baudRateBox->addItem(SerialSettingsHelper::BaudToText(QSerialPort::Baud1200), QSerialPort::Baud1200);
    m_ui->baudRateBox->addItem(SerialSettingsHelper::BaudToText(QSerialPort::Baud2400), QSerialPort::Baud2400);
    m_ui->baudRateBox->addItem(SerialSettingsHelper::BaudToText(QSerialPort::Baud4800), QSerialPort::Baud4800);
    m_ui->baudRateBox->addItem(SerialSettingsHelper::BaudToText(QSerialPort::Baud9600), QSerialPort::Baud9600);
    m_ui->baudRateBox->addItem(SerialSettingsHelper::BaudToText(QSerialPort::Baud19200), QSerialPort::Baud19200);
    m_ui->baudRateBox->addItem(SerialSettingsHelper::BaudToText(QSerialPort::Baud38400),QSerialPort::Baud38400);
    m_ui->baudRateBox->addItem(SerialSettingsHelper::BaudToText(QSerialPort::Baud57600),QSerialPort::Baud57600);
    m_ui->baudRateBox->addItem(SerialSettingsHelper::BaudToText(QSerialPort::Baud115200),QSerialPort::Baud115200);
    m_ui->dataBitsBox->setCurrentIndex(3);

    //m_ui->baudRateBox->addItem(tr("Custom"));

    m_ui->dataBitsBox->addItem(SerialSettingsHelper::DataBitsToText(QSerialPort::Data5),QSerialPort::Data5);
    m_ui->dataBitsBox->addItem(SerialSettingsHelper::DataBitsToText(QSerialPort::Data6),QSerialPort::Data6);
    m_ui->dataBitsBox->addItem(SerialSettingsHelper::DataBitsToText(QSerialPort::Data7),QSerialPort::Data7);
    m_ui->dataBitsBox->addItem(SerialSettingsHelper::DataBitsToText(QSerialPort::Data8),QSerialPort::Data8);
    m_ui->dataBitsBox->setCurrentIndex(3);

    m_ui->parityBox->addItem(SerialSettingsHelper::ParityToText(QSerialPort::NoParity), QSerialPort::NoParity);
    m_ui->parityBox->addItem(SerialSettingsHelper::ParityToText(QSerialPort::EvenParity), QSerialPort::EvenParity);
    m_ui->parityBox->addItem(SerialSettingsHelper::ParityToText(QSerialPort::OddParity), QSerialPort::OddParity);
    m_ui->parityBox->addItem(SerialSettingsHelper::ParityToText(QSerialPort::MarkParity), QSerialPort::MarkParity);
    m_ui->parityBox->addItem(SerialSettingsHelper::ParityToText(QSerialPort::SpaceParity), QSerialPort::SpaceParity);

    m_ui->stopBitsBox->addItem(SerialSettingsHelper::StopBitsToText(QSerialPort::OneStop), QSerialPort::OneStop);
#ifdef Q_OS_WIN
    m_ui->stopBitsBox->addItem(SerialSettingsHelper::StopBitsToText(QSerialPort::OneAndHalfStop), QSerialPort::OneAndHalfStop);
#endif
    m_ui->stopBitsBox->addItem(SerialSettingsHelper::StopBitsToText(QSerialPort::TwoStop), QSerialPort::TwoStop);

    m_ui->flowControlBox->addItem(SerialSettingsHelper::FlowControlToText(QSerialPort::NoFlowControl), QSerialPort::NoFlowControl);
    m_ui->flowControlBox->addItem(SerialSettingsHelper::FlowControlToText(QSerialPort::HardwareControl), QSerialPort::HardwareControl);
    m_ui->flowControlBox->addItem(SerialSettingsHelper::FlowControlToText(QSerialPort::SoftwareControl), QSerialPort::SoftwareControl);
}

void SettingsDialog::fillPortsInfo()
{
    m_ui->serialPortInfoListBox->clear();
    QString description;
    QString manufacturer;
    QString serialNumber;
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {
        QStringList list;
        description = info.description();
        manufacturer = info.manufacturer();
        serialNumber = info.serialNumber();
        list << info.portName()
             << (!description.isEmpty() ? description : blankString)
             << (!manufacturer.isEmpty() ? manufacturer : blankString)
             << (!serialNumber.isEmpty() ? serialNumber : blankString)
             << info.systemLocation()
             << (info.vendorIdentifier() ? QString::number(info.vendorIdentifier(), 16) : blankString)
             << (info.productIdentifier() ? QString::number(info.productIdentifier(), 16) : blankString);

        m_ui->serialPortInfoListBox->addItem(list.first(), list);
    }

    m_ui->serialPortInfoListBox->addItem(tr("Custom"));
}

void SettingsDialog::ReadSettings()
{
    _currentSettings.portName = m_ui->serialPortInfoListBox->currentText();

    bool ok;
    int baudRate_ix = m_ui->baudRateBox->currentIndex();
    int baudRate_int = m_ui->baudRateBox->itemData(baudRate_ix).toInt(&ok);
    if(ok)
    {
        _currentSettings.baudRate = static_cast<QSerialPort::BaudRate>(baudRate_int);
    }
    else
    {
        _currentSettings.baudRate = QSerialPort::BaudRate::UnknownBaud;
    }
    //_currentSettings.stringBaudRate = QString::number(_currentSettings.baudRate);

    _currentSettings.dataBits = static_cast<QSerialPort::DataBits>(
                m_ui->dataBitsBox->itemData(m_ui->dataBitsBox->currentIndex()).toInt());
    //_currentSettings.stringDataBits = m_ui->dataBitsBox->currentText();

    _currentSettings.parity = static_cast<QSerialPort::Parity>(
                m_ui->parityBox->itemData(m_ui->parityBox->currentIndex()).toInt());
    //_currentSettings.stringParity = m_ui->parityBox->currentText();

    _currentSettings.stopBits = static_cast<QSerialPort::StopBits>(
                m_ui->stopBitsBox->itemData(m_ui->stopBitsBox->currentIndex()).toInt());
    //_currentSettings.stringStopBits = m_ui->stopBitsBox->currentText();

    _currentSettings.flowControl = static_cast<QSerialPort::FlowControl>(
                m_ui->flowControlBox->itemData(m_ui->flowControlBox->currentIndex()).toInt());
    //_currentSettings.stringFlowControl = m_ui->flowControlBox->currentText();

    _currentSettings.localEchoEnabled = m_ui->localEchoCheckBox->isChecked();
}

void SettingsDialog::on_pushButton_clicked()
{
    fillPortsInfo();
}
