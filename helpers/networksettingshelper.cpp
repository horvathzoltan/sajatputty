#include "networksettingshelper.h"

QString NetworkSettingsHelper::LogMode_ToText(LogMode v)
{
    if(v == LogMode::Log) return "Log";
    if(v == LogMode::Echo) return "Echo";
    return "unknown";
}

LogMode NetworkSettingsHelper::To_LogMode(const QString& v)
{
    if(v == "Log") return LogMode::Log;
    if(v == "Echo") return LogMode::Echo;
    return LogMode::Echo;
}


QString NetworkSettingsHelper::ChanelMode_ToText(ChanelMode v)
{
    if(v == ChanelMode::RX) return "RX";
    if(v == ChanelMode::TX) return "TX";
    if(v == ChanelMode::RXTX) return "RXTX";
    if(v == ChanelMode::None) return "None";
    return "unknown";
}

ChanelMode NetworkSettingsHelper::To_ChanelMode(const QString& v)
{
    if(v == "RX") return ChanelMode::RX;
    if(v == "TX") return ChanelMode::TX;
    if(v == "RXTX") return ChanelMode::RXTX;
    if(v == "None") return ChanelMode::None;
    return ChanelMode::None;
}


