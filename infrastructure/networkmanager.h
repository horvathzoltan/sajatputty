#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include "viewmodels/networksettingsvm.h"
class NetworkManager{
public:
    QString ip;
    int port;
    QString messageTemplate;
    
    void saveSettings(const QString& _settingsFn);
    NetworkSettingsVM getSettings();
    void loadSettings(const QString& _settingsFn);
    void setSettings(const NetworkSettingsVM& m);
};

#endif // NETWORKMANAGER_H
