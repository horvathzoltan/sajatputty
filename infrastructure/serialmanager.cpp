
#include "serialmanager.h"

#include "serialdata.h"

#include <helpers/filenamehelper.h>
#include <helpers/serialsettingshelper.h>

#include <QSettings>

void SerialManager::setSettings(const SerialSettingsVM &p){
    _serial.setPortName(p.portName);
    _serial.setBaudRate(p.baudRate);
    _serial.setDataBits(p.dataBits);
    _serial.setParity(p.parity);
    _serial.setStopBits(p.stopBits);
    _serial.setFlowControl(p.flowControl);
}

SerialSettingsVM SerialManager::getSettings()
{
    SerialSettingsVM p;
    p.portName = _serial.portName();
    
    qint32 baudRate_int = _serial.baudRate();
    QSerialPort::BaudRate baudRate = static_cast<QSerialPort::BaudRate>(baudRate_int);
    p.baudRate = baudRate;
    
    p.dataBits = _serial.dataBits();
    p.parity = _serial.parity();
    p.stopBits = _serial.stopBits();
    p.flowControl = _serial.flowControl();
    p.localEchoEnabled = false;
    
    return p;
}

SerialManager::SerialManager()
{
    //_serial = new QSerialPort();
}

bool SerialManager::openSerialPort()
{
    return _serial.open(QIODevice::ReadWrite);
}

void SerialManager::closeSerialPort()
{
    if (_serial.isOpen())
        _serial.close();
}

QString SerialManager::MSerial_ToString(bool localEcho)
{
    return SerialSettingsHelper::MSerial_ToString(&_serial);
}

// void SerialManager::saveSettings(const QString& fn, bool localEcho)
// {
//     SerialSettingsHelper::saveSettings(fn, &_serial,localEcho);
// }

// void SerialManager::loadSettings(const QString&fn, bool* localEcho )
// {
//     SerialSettingsHelper::loadSettings(fn, &_serial, localEcho);
// }

void SerialManager::writeData(const SerialData &data)
{
    _serial.write(data.data());
}

QByteArray SerialManager::readAll()
{
    return _serial.readAll();
}


void SerialManager::loadSettings(const QString& _settingsFn, bool* localEcho)
{
    if(_settingsFn.isEmpty()) return;
    if(!FileNameHelper::IsFileExists(_settingsFn)) return;
    if(!localEcho) return;

    QSettings settings(_settingsFn, QSettings::NativeFormat);
    _serial.setPortName(settings.value("name").toString());
    _serial.setBaudRate(settings.value("baudRate").toInt());
    _serial.setDataBits(SerialSettingsHelper::To_DataBits( settings.value("dataBits").toString()));
    _serial.setStopBits(SerialSettingsHelper::To_StopBits(settings.value("stopBits").toString()));
    _serial.setParity(SerialSettingsHelper::To_ParityBits(settings.value("parityBits").toString()));
    _serial.setFlowControl(SerialSettingsHelper::To_FlowControl(settings.value("flowcontrol").toString()));

    *localEcho = SerialSettingsHelper::To_Bool(settings.value("localEcho").toString());
}

void SerialManager::saveSettings(const QString& _settingsFn, bool localEcho)
{
    if(_settingsFn.isEmpty()) return;

    QSettings settings(_settingsFn, QSettings::NativeFormat);

    QString name = _serial.portName();
    settings.setValue("name", name);

    settings.setValue("baudRate", _serial.baudRate());
    settings.setValue("dataBits", SerialSettingsHelper::DataBits_ToText(_serial.dataBits()));
    settings.setValue("stopBits", SerialSettingsHelper::StopBits_ToText(_serial.stopBits()));
    settings.setValue("parityBits", SerialSettingsHelper::ParityBits_ToText(_serial.parity()));
    settings.setValue("flowcontrol", SerialSettingsHelper::FlowControl_ToText(_serial.flowControl()));

    settings.setValue("localEcho", localEcho?"enabled":"disabled");
}
