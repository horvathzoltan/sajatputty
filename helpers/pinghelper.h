#ifndef PINGHELPER_H
#define PINGHELPER_H

#include <QHostAddress>


class PingHelper
{
public:
    PingHelper();

    struct PingModel{
        quint32 packSize=0;
        QString fromIp;
        quint16 icmpSeq=0;
        quint8 ttl=0;
        qreal time = 0;

        QString ToString();
        void Parse(const QString& txt);
    };

    struct PingResult_1
    {
        PingModel _ping;
        qreal _time = 0;
        bool ok = false;
    };

    struct PingResult_Many
    {
        QList<PingModel> _pings;
        qreal _time = 0;
        bool ok = false;
    };

    static PingResult_1 Ping_1(const QHostAddress& host, quint32 timeoutMillis, quint32 loopMax);
    static PingResult_Many Ping_Many(const QHostAddress& host, quint32 timeoutMillis, quint32 loopMax);
};

#endif // PINGHELPER_H
