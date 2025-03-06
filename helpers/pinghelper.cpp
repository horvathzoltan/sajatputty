#include "pinghelper.h"
#include "processhelper.h"
#include "qcoreapplication.h"

#include <QElapsedTimer>
#include <QProcessEnvironment>

PingHelper::PingHelper() {}

PingHelper::PingResult_1 PingHelper::Ping_1(const QHostAddress& host, quint32 time, quint32 loopMax)
{
    static QProcessEnvironment env = QProcessEnvironment::systemEnvironment();

    QProcess process;
    QString hostName = host.toString();

    PingHelper::PingResult_1 r;

    QString cmd = QStringLiteral("ping -c%1 -w%2 %3").arg(loopMax).arg(time).arg(host)
    ProcessHelper::Output o = ProcessHelper::ShellExecute(cmd);

    r.ok = exitCode==0;

    if(r.ok){
        r._ping.Parse(stdOut);
    }

    return r;
}


PingHelper::PingResult_Many PingHelper::Ping_Many(const QHostAddress& host, quint32 timeoutMillis, quint32 loopMax)
{
    static QProcessEnvironment env = QProcessEnvironment::systemEnvironment();

    QProcess process;
    QString hostName = host.toString();

    PingHelper::PingResult_Many r;

    // r.ok = false;
    // r.fromIp = hostName;
    // r.packSize = 0;
    // r.icmpSeq = 0;
    // r.ttl = 0;

    // process beállítása
    // workaround - https://bugreports.qt.io/browse/QTBUG-2284
    env.insert("LD_LIBRARY_PATH", "/usr/lib");
    process.setProcessEnvironment(env);
    QString path = qApp->applicationDirPath();
    process.setWorkingDirectory(path);


    QStringList l = {};
    QString cmd("for a in {1..254}; do ping -c5 -w5 172.16.1.${a}& done|grep from");
    // process indítása
    QElapsedTimer t;
    t.start();
    process.start(cmd, l);
    if(!process.waitForStarted()) return r;
    process.waitForFinished();//timeoutMillis);

    r._time = t.elapsed();
    //ProcessHelper::Output o;
    //auto elapsedMillis = t.elapsed();
    QByteArray stdOut = process.readAllStandardOutput();
    //auto stdErr = process.readAllStandardError();
    int exitCode = process.exitCode();

    r.ok = exitCode==0;

    if(r.ok){

    }

    return r;
}

void PingHelper::PingModel::Parse(const QString &txt)
{

}
