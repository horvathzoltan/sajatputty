#ifndef NETWORKSETTINGSHELPER_H
#define NETWORKSETTINGSHELPER_H

#include "infrastructure/chanelmode.h"
#include "infrastructure/logmode.h"

#include <QString>
class NetworkSettingsHelper
{
public:
    static QString LogMode_ToText(LogMode v);
    static LogMode To_LogMode(const QString& v);
    static QString ChanelMode_ToText(ChanelMode v);
    static ChanelMode To_ChanelMode(const QString& v);
};


#endif // NETWORKSETTINGSHELPER_H
