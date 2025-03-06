#ifndef NETWORKHELPER_H
#define NETWORKHELPER_H

#include <QString>


class NetworkHelper
{
public:
    NetworkHelper();

    static QString GetLocalIp();
    static QString GetLocalIp_Wired();
};

#endif // NETWORKHELPER_H

