#ifndef SERIALMANAGER_H
#define SERIALMANAGER_H

#include "viewmodels/serialsettingsvm.h"
#include <QSerialPort>


class SerialManager{
private:
    QSerialPort _serial;
public:
    void setSettings(const SerialSettingsVM &p);
    SerialSettingsVM getSettings();
    bool openSerialPort();
    void closeSerialPort();
    QString errorString(){return _serial.errorString();}
    
    QString MSerial_ToString(bool localEcho);
    void saveSettings(const QString& fn, bool localEcho);
    void loadSettings(const QString&fn, bool* localEcho);
    void writeData(const QByteArray &data);
    QByteArray readAll();
    
    const QSerialPort* serial_ptr(){return &_serial;}
public:
    SerialManager();
};

#endif // SERIALMANAGER_H
