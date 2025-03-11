
#include "serialmanager.h"

#include <helpers/serialsettingshelper.h>

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

void SerialManager::saveSettings(const QString& fn, bool localEcho)
{
    SerialSettingsHelper::saveSettings(fn, &_serial,localEcho);
}

void SerialManager::loadSettings(const QString&fn, bool* localEcho )
{
    SerialSettingsHelper::loadSettings(fn, &_serial, localEcho);
}

void SerialManager::writeData(const QByteArray &data)
{
    _serial.write(data);
}

QByteArray SerialManager::readAll()
{
    return _serial.readAll();
}
