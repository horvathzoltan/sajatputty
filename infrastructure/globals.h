#ifndef GLOBALS_H
#define GLOBALS_H

#include "../helpers/sysinfohelper.h"

#include <helpers/networkmonitor.h>
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
public:
    Globals(){};

};

#endif // GLOBALS_H
