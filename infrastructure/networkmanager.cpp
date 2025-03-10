#include <QSettings>

#include <helpers/filenamehelper.h>

#include "networkmanager.h"
#include "globals.h"

extern Globals _globals;

NetworkSettingsVM NetworkManager::getSettings()
{
    NetworkSettingsVM p;
    
    p.deviceIp = _globals._helpers._sysinfoHelper.hostip();
    p.serverIp = ip;//"172.16.1.5";
    p.serverPort = port;//8081;
    p.messageTemplate = messageTemplate;//"makk";
    
    return p;
}

void NetworkManager::loadSettings(const QString& _settingsFn)
{
    if(_settingsFn.isEmpty()) return;
    if(!FileNameHelper::IsFileExists(_settingsFn)) return;

    QSettings settings(_settingsFn, QSettings::NativeFormat);
    ip = settings.value("ip").toString();
    port = settings.value("port").toInt();
    messageTemplate = settings.value("template").toString();
}

void NetworkManager::setSettings(const NetworkSettingsVM &m)
{
    ip = m.serverIp;
    port = m.serverPort;
    messageTemplate = m.messageTemplate;
}

void NetworkManager::saveSettings(const QString& _settingsFn)
{
    if(_settingsFn.isEmpty()) return;

    QSettings settings(_settingsFn, QSettings::NativeFormat);
    settings.setValue("ip", ip);
    settings.setValue("port", port);
    settings.setValue("template", messageTemplate);
}
