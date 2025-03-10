#ifndef GLOBALS_H
#define GLOBALS_H

#include "../helpers/sysinfohelper.h"
//#include "console.h"
#include "networkmanager.h"
#include "serialmanager.h"
#include "session.h"
//#include "viewmodels/serialsettingsvm.h"

#include <helpers/networkmonitor.h>
//#include <helpers/serialsettingshelper.h>

//#include <QSerialPort>
//#include "helpers/filenamehelper.h"

class Helpers{
public:
    SysInfoHelper _sysinfoHelper;
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
    Globals(){};

    const QSerialPort* serial_ptr(){
        return _serialManager.serial_ptr();
    };
};

#endif // GLOBALS_H
