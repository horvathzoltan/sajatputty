#include "networkhelper.h"

#include <QHostInfo>
#include <QNetworkInterface>

NetworkHelper::NetworkHelper() {}

QString NetworkHelper::GetLocalIp()
{
    QString localhostIP;
    QList<QHostAddress> hostList = QNetworkInterface::allAddresses();//QHostInfo::fromName(localhostname).addresses();
    for (QHostAddress& address:hostList) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address.isLoopback() == false)
        {
            localhostIP = address.toString();
            break;
        }
    }
    // QString localMacAddress;
    // //QString localNetmask;
    // foreach (const QNetworkInterface& networkInterface, QNetworkInterface::allInterfaces()) {
    //     foreach (const QNetworkAddressEntry& entry, networkInterface.addressEntries()) {
    //         if (entry.ip().toString() == localhostIP) {
    //             localMacAddress = networkInterface.hardwareAddress();
    //             //localNetmask = entry.netmask().toString();
    //             break;
    //         }
    //     }
    // }
    return localhostIP;
}

QString NetworkHelper::GetLocalIp_Wired()
{
    QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();
    for (QNetworkInterface &interface : interfaces)
    {
        // Check if the interface is active and not a loopback
        if (interface.flags().testFlag(QNetworkInterface::IsUp) &&
            interface.flags().testFlag(QNetworkInterface::IsRunning) &&
            !interface.flags().testFlag(QNetworkInterface::IsLoopBack)
            )
        {
            QNetworkInterface::InterfaceType type = interface.type();
            bool wired = type == QNetworkInterface::Ethernet && type != QNetworkInterface::Wifi;

            if (wired)
            {
                QList<QNetworkAddressEntry> entries = interface.addressEntries();
                for (QNetworkAddressEntry &entry : entries)
                {
                    if (entry.ip().protocol() == QAbstractSocket::IPv4Protocol)
                    {
                        return entry.ip().toString();
                    }
                }
            }
        }
    }
    return {};
}
