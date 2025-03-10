#ifndef GLOBALS_H
#define GLOBALS_H

#include "../helpers/sysinfohelper.h"
#include "console.h"
#include "session.h"
#include "viewmodels/serialsettingsvm.h"

#include <helpers/networkmonitor.h>
#include <helpers/serialsettingshelper.h>

#include <QSerialPort>
//#include "helpers/filenamehelper.h"

class Helpers{
public:
    SysInfoHelper _sysinfoHelper;
};

class SerialManager{
private:
    QSerialPort _serial;
public:
    void setSerialSettings(const SerialSettingsVM &p);
    SerialSettingsVM getSerialSettings();
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

class NetworkManager{
public:
    void saveSettings(){};
};

class Globals
{
public:        
    Helpers _helpers;    
    NetworkMonitor _networkMonitor;
    SerialManager _serialManager;
    NetworkManager _networkManager;
    SessionLog _sessionLog;
public:
    Globals(){
       // _serial = new QSerialPort();
    };

    const QSerialPort* serial_ptr(){
        return _serialManager.serial_ptr();
    };


};

#endif // GLOBALS_H
