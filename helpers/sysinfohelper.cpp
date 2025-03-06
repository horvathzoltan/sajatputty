#include "sysinfohelper.h"

#include "networkhelper.h"

//started biovitality as zoli@hercules
//started biovitality as zoli@pif

void SysInfoHelper::Init(const QString &t, const QString &b)
{
    isInited = false;
    _target = t;
    _buildNumber = b;
    _user = qgetenv("USER");
    _hostName = QSysInfo::machineHostName();
    isInited = true;
    _hostIp = NetworkHelper::GetLocalIp_Wired();
}

bool SysInfoHelper::hasBuildNumber(){
    if(_buildNumber.isEmpty()) return false;
    if(_buildNumber=="-1") return false;
    return true;
}

QString SysInfoHelper::Get_SysInfo()
{
    if(!isInited) return {};

    QString msg = _target;
    if(hasBuildNumber())
    {
        msg+="("+_buildNumber+")";
    }

    if(!_user.isEmpty()){
        msg += +" as "+_user;
    }


    if(!_hostIp.isEmpty())
    {
        msg+="@"+_hostIp;

        if(!_hostName.isEmpty())
        {
            msg+="("+_hostName+")";
        }
    }
    else
    {
        if(!_hostName.isEmpty())
        {
            msg+="@"+_hostName;
        }
    }

    return msg;
}


