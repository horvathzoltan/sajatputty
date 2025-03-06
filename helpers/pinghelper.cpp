#include "pinghelper.h"
#include "processhelper.h"
#include "qcoreapplication.h"

#include <QElapsedTimer>
#include <QRegularExpression>
#include <QStringLiteral>

PingHelper::PingHelper() {}

PingHelper::PingResult_1 PingHelper::Ping_1(const QHostAddress& host, quint32 time, quint32 loopMax)
{
    QString hostName = host.toString();

    PingHelper::PingResult_1 r;

    QString cmd = QStringLiteral("ping -c%1 -w%2 %3 | grep from").arg(loopMax).arg(time).arg(hostName);
    ProcessHelper::Output o = ProcessHelper::ShellExecute(cmd);

    r._elapsedMillis = o.elapsedMillis;
    r.ok = o.exitCode==0;
    if(r.ok)
    {
        QStringList l = o.stdOut.split("\n");
        if(!l.isEmpty())
        {
            if(!l[0].isEmpty())
            {
                r._ping.Parse(l[0]);
            }
        }
    }

    return r;
}


PingHelper::PingResult_Many PingHelper::Ping_Many(const QHostAddress& host, quint32 time, quint32 loopMax)
{
    //static QProcessEnvironment env = QProcessEnvironment::systemEnvironment();

    //QProcess process;
    QString hostName = host.toString();

    int ix = hostName.lastIndexOf(".");
    if(ix>0){
        hostName = hostName.left(ix);
    }
    PingHelper::PingResult_Many r;

    QStringList l = {};
    QString cmd= QStringLiteral("for a in $(seq 1 254); do ping -c%1 -w%2 %3.${a}& done | grep from").arg(loopMax).arg(time).arg(hostName);
    // process indítása
    ProcessHelper::Output o = ProcessHelper::ShellExecute(cmd);

    r._elapsedMillis = o.elapsedMillis;
    r.ok = o.exitCode==0;
    if(r.ok)
    {
        QStringList l = o.stdOut.split("\n");
        for(auto &s : l)
        {
            if(s.isEmpty()) continue;
            PingHelper::PingModel p;
            p.Parse(s);

            r.append(p);
        }
    }

    return r;
}

void PingHelper::PingModel::Parse(const QString &txt)
{
    static QRegularExpression regex(R"(([\d\.]+) bytes from ([\d\.]+): .*icmp_seq=(\d+) .*ttl=(\d+) time=([\d\.]+))");

    QRegularExpressionMatch match = regex.match(txt);

    if (match.hasMatch())
    {
        packSize = match.captured(1).toUInt();
        fromIp = match.captured(2);
        icmpSeq = match.captured(3).toUInt();
        ttl = match.captured(4).toUInt();
        time = match.captured(5).toDouble();
    }
}

void PingHelper::PingResult_Many::append(const PingModel& m)
{
    bool isContains = contains(m);
    if(!isContains)
    {
        _pings.append(m);
    }
}

QStringList PingHelper::PingResult_Many::GetHosts()
{
    QStringList r;
    for (auto &a : _pings)
    {
        r.append(a.fromIp);
    }
    return r;
}

bool PingHelper::PingResult_Many::contains(const PingModel& m)
{
    for(auto&a:_pings)
    {
        if(a.fromIp==m.fromIp)
        {
            return true;
        }
    }
    return false;
}
