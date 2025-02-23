#ifndef GLOBALS_H
#define GLOBALS_H

#include "sysinfohelper.h"
#include <QDir>

class Helpers{
public:
    SysInfoHelper _sysinfoHelper;
};

class Globals
{
public:

    Helpers _helpers;

private:
    QString _logDirName = "terminal_logs";
    QString _logFileName = "terminal.log";
    QString _settingsFileName = "terminal_settings";
    QString _homePath = QDir::homePath();

public:
    Globals(){};

    QString terminalLogPath(){return QDir(_homePath).filePath(_logFileName);}
    QString homePath(){return _homePath;}

};

#endif // GLOBALS_H
