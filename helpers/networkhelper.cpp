#include "networkhelper.h"

#include "pinghelper.h"
#include "processhelper.h"

#include <QHostInfo>
#include <QNetworkInterface>
#include <QRegularExpression>

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

NetworkHelper::NetworkModel NetworkHelper::GetLocalIp_Wired()
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
                        NetworkModel m(
                            entry.ip(),
                            interface.index(),
                            interface.name(),
                            NetworkModel::NetworkType::Wired
                            );
                        return m;
                    }
                }
            }
        }
    }
    return {};
}

QMap<QString,QSet<int>> NetworkHelper::FindHost_ByPorts(const QStringList& hosts, const QList<int>& ports)
{
    QMap<QString,QSet<int>> r;
    // for(auto &host : hosts)
    // {
    //     for(auto &port : ports)
    //     {
            //QString cmd = QStringLiteral("nc -z -w 1 %1 %2").arg(host).arg(port);
            QString htxt = hosts.join(" ");
            QString ptxt;
            for(auto &port : ports)
            {
                ptxt.append(QString::number(port)).append(" ");
            }
            //QString cmd = QStringLiteral("for a in %1; do for b in %2; do nc -z -w 1 ${a} ${b}& done done | grep suc").arg(htxt).arg(ptxt);
            //QString cmd = QStringLiteral("for a in %1 ; do nc -z -w 1 $a 22& done | grep suc").arg(htxt).arg(ptxt);
            QString cmd = QStringLiteral("for host in %1; do for port in %2; do nc -z -w 1 $host $port -v 2>&1 & done; done | grep suc").arg(htxt).arg(ptxt);
            ProcessHelper::Output o = ProcessHelper::ShellExecute(cmd);
            if(o.exitCode==0)
            {
                QStringList e = o.stdOut.split("\n");
                static QRegularExpression regex(R"(to ([\d\.]+) +(\d+) port)");
                for(auto &s : e)
                {
                    if(s.isEmpty()) continue;
                    QRegularExpressionMatch match = regex.match(s);
                    if (match.hasMatch())
                    {
                        QString h = match.captured(1);
                        QString p = match.captured(2);
                        bool ok;
                        int port = p.toInt(&ok);
                        if(ok)
                        {
                            if(!r.contains(h))
                            {
                                r.insert(h, {port});
                            }
                            else{
                                r[h].insert(port);
                            }
                        }
                    }
                }
            }
    //     }
    // }
    return r;
}

QStringList NetworkHelper::HostsByPorts_ToString(const QMap<QString, QSet<int>>& m)
{
    QStringList a;

    for(auto &k : m.keys())
    {
        QString p;
        for(auto &v : m[k])
        {
            if(!p.isEmpty()) p.append(",");
            p.append(QString::number(v));
        }
        a.append(k+":"+p);
    }

    return a;
}

QStringList NetworkHelper::HostsByPorts_ToString2(const QMap<QString, QSet<int>>& m)
{
    QStringList a;

    for(auto &k : m.keys())
    {
        a.append(k);
    }

    return a;
}

bool NetworkHelper::isConnected_ByInterfaceIndex(int ix)
{
    QNetworkInterface interface = QNetworkInterface::interfaceFromIndex(ix);


    bool isConnected = interface.flags().testFlag(QNetworkInterface::IsUp) &&
        interface.flags().testFlag(QNetworkInterface::IsRunning) &&
                       !interface.flags().testFlag(QNetworkInterface::IsLoopBack);

    return isConnected;
}

QStringList NetworkHelper::FindHosts_ByPorts(const QString &host, const QList<int> &ports)
{
    QHostAddress hostAddress(host);
    auto p2 = PingHelper::Ping_Many(hostAddress, 5, 5);
    QStringList p22 = p2.GetHosts();
    QMap<QString,QSet<int>> p3 = NetworkHelper::FindHost_ByPorts(p22, ports);

    QList<QString> p3txt = p3.keys();

    //QStringList p3txt = NetworkHelper::HostsByPorts_ToString2(p3);
    return p3txt;
}

