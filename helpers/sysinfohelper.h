#ifndef SYSINFOHELPER_H
#define SYSINFOHELPER_H

#include "networkhelper.h"

#include <QString>

class SysInfoHelper
{
private:
    QString _target;
    QString _buildNumber;
    QString _user;
    QString _hostName;
    NetworkHelper::NetworkModel _network;

    bool hasBuildNumber();

    bool isInited = false;
public:
    void Init(const QString& t, const QString& b);
    void InitNetwork();
    QString Get_SysInfo();
    QString hostName(){return _hostName;}
    QHostAddress hostAddress(){return _network.hostAddress();}
    QString hostip(){return _network.ip();}
    int networkInterfaceIx(){return _network.interfaceIx();}
    QString user(){return _user;}
private:
    QString GetLocalIp();
};

#endif // SYSINFOHELPER_H
