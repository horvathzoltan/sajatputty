#include "sysinfohelper.h"

#include "networkhelper.h"
#include <unistd.h>
#include <pwd.h>

//started biovitality as zoli@hercules
//started biovitality as zoli@pif

void SysInfoHelper::Init(const QString &t, const QString &b)
{
    isInited = false;
    _target = t;
    _buildNumber = b;
    _user = qgetenv("USER");
    if(_user.isEmpty()){
        _user = qgetenv("USERNAME");
    } if(_user.isEmpty()){
        struct passwd *pw = getpwuid(getuid());
        if(pw){
            _user = pw->pw_name;
        }
    }
    _hostName = QSysInfo::machineHostName();
    isInited = true;
    _network = NetworkHelper::GetLocalIp_Wired();
}

void SysInfoHelper::InitNetwork()
{
    _network = NetworkHelper::GetLocalIp_Wired();
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

    QString _hostIp = _network.ip();

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


