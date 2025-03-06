#ifndef SYSINFOHELPER_H
#define SYSINFOHELPER_H

#include <QString>

class SysInfoHelper
{
private:
    QString _target;
    QString _buildNumber;
    QString _user;
    QString _hostName;
    QString _hostIp;

    bool hasBuildNumber();

    bool isInited = false;
public:
    void Init(const QString& t, const QString& b);
    QString Get_SysInfo();
    QString hostName(){return _hostName;}

private:
    QString GetLocalIp();
};

#endif // SYSINFOHELPER_H
