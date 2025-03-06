#ifndef NETWORKHELPER_H
#define NETWORKHELPER_H

#include <QString>


class NetworkHelper
{
public:
    NetworkHelper();

    static QString GetLocalIp();
    static QString GetLocalIp_Wired();
    static QMap<QString,QSet<int>> FindHost_ByPorts(const QStringList& hosts, const QList<int>& ports);
};

#endif // NETWORKHELPER_H

