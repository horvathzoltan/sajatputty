#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include "viewmodels/networksettingsvm.h"

class NetworkManager{
public:        
private:
    QString _tag;
    QString _ip;
    int _port;
    //QString messageTemplate;
    LogMode _logMode;
    ChanelMode _chanelMode;

public:
    LogMode logMode(){return _logMode;}
    ChanelMode chanelMode(){return _chanelMode;}

    void saveSettings(const QString& _settingsFn);
    NetworkSettingsVM getSettings();
    void loadSettings(const QString& _settingsFn);
    void setSettings(const NetworkSettingsVM& m);

};


#endif // NETWORKMANAGER_H
