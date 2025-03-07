#ifndef NETWORKHELPER_H
#define NETWORKHELPER_H

#include <QHostAddress>
#include <QString>


class NetworkHelper
{
public:
    NetworkHelper();

    struct NetworkModel
    {
        enum NetworkType:int{Unknown=0, Wired, Wireless};
    private:
        QString _name;
        QHostAddress _ip;
        int _interfaceIx = 0;
        NetworkType _type = NetworkType::Unknown;

    public:
        NetworkModel(){};
        NetworkModel(const QHostAddress& ip, int ix, const QString& name, NetworkType type)
        {
            _name = name;
            _ip = ip;
            _interfaceIx = ix;
            _type = type;
        };

        QHostAddress hostAddress(){return _ip;}
        QString ip(){return _ip.toString();}
        int interfaceIx(){return _interfaceIx;}
    };

    static QString GetLocalIp();
    static NetworkModel GetLocalIp_Wired();
    static QMap<QString,QSet<int>> FindHost_ByPorts(const QStringList& hosts, const QList<int>& ports);
    static QStringList HostsByPorts_ToString(const QMap<QString, QSet<int>>& m);
    static QStringList HostsByPorts_ToString2(const QMap<QString, QSet<int>>& m);
    static bool isConnected_ByInterfaceIndex(int ix);

    static QStringList FindHosts_ByPorts(const QString& host, const QList<int>& ports);
};

#endif // NETWORKHELPER_H

