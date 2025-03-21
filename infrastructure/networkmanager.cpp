#include <QSettings>

#include <helpers/filenamehelper.h>
#include <helpers/networksettingshelper.h>

#include "networkmanager.h"
#include "globals.h"

extern Globals _globals;

NetworkSettingsVM NetworkManager::getSettings()
{
    NetworkSettingsVM p;
    
    p.deviceIp = _globals._helpers._sysinfoHelper.hostip();
    p.serverIp = _ip;//"172.16.1.5";
    p.serverPort = _port;//8081;
    //p.messageTemplate = messageTemplate;//"makk";
    p.logMode = _logMode;
    p.deviceTag = _tag;
    p.chanelMode = _chanelMode;

    return p;
}

void NetworkManager::setSettings(const NetworkSettingsVM &m)
{
    _tag = m.deviceTag;
    _ip = m.serverIp;
    _port = m.serverPort;
    _logMode = m.logMode;
    _chanelMode = m.chanelMode;
    //messageTemplate = m.messageTemplate;
}

void NetworkManager::loadSettings(const QString& _settingsFn)
{
    if(_settingsFn.isEmpty()) return;
    if(!FileNameHelper::IsFileExists(_settingsFn)) return;

    QSettings settings(_settingsFn, QSettings::NativeFormat);
    _tag = settings.value("tag").toString();
    _ip = settings.value("ip").toString();
    _port = settings.value("port").toInt();
    auto logmode0 = settings.value("logMode");
    auto chanelmode0 = settings.value("chanelMode");
    auto logmode =  NetworkSettingsHelper::To_LogMode(logmode0.toString());
    auto chanelmode = NetworkSettingsHelper::To_ChanelMode(chanelmode0.toString());
    _logMode = logmode;
    _chanelMode = chanelmode;
    //messageTemplate = settings.value("template").toString();
}

void NetworkManager::saveSettings(const QString& _settingsFn)
{
    if(_settingsFn.isEmpty()) return;

    QSettings settings(_settingsFn, QSettings::NativeFormat);
    settings.setValue("tag", _tag);
    settings.setValue("ip", _ip);
    settings.setValue("port", _port);
    settings.setValue("logMode", NetworkSettingsHelper::LogMode_ToText(_logMode));
    settings.setValue("chanelMode", NetworkSettingsHelper::ChanelMode_ToText(_chanelMode));
    //settings.setValue("template", _messageTemplate);
}
