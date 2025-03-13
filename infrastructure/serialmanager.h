#ifndef SERIALMANAGER_H
#define SERIALMANAGER_H

#include "viewmodels/serialsettingsvm.h"
#include "serialdata.h"
#include <QSerialPort>

class SerialManager
{
private:
    QSerialPort _serial;
public:
    SerialManager();
    void setSettings(const SerialSettingsVM &p);
    SerialSettingsVM getSettings();
    bool openSerialPort();
    void closeSerialPort();
    QString errorString(){return _serial.errorString();}
    
    QString MSerial_ToString(bool localEcho);
    //void saveSettings(const QString& fn, bool localEcho);
    //void loadSettings(const QString&fn, bool* localEcho);
    void writeData(const SerialData &data);
    QByteArray readAll();
    
    const QSerialPort* serial_ptr(){return &_serial;}

    void loadSettings(const QString& fn, bool* localEcho);
    void saveSettings(const QString& fn, bool localEcho);
};

#endif // SERIALMANAGER_H
