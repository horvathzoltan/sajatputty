#include <QApplication>
#include <QDebug>

#include <helpers/filenamehelper.h>
#include <helpers/networkhelper.h>
#include <helpers/networkmonitor.h>
#include <helpers/pinghelper.h>
#include <helpers/serialsettingshelper.h>

#include "mainwindow.h"
#include "infrastructure/buildnumber.h"
#include "helpers/stringify.h"
#include "helpers/signalhelper.h"

#include "infrastructure/globals.h"

Globals _globals;

int main(int argc, char *argv[])
{
    SignalHelper::setShutDownSignal(SignalHelper::SIGINT_); // shut down on ctrl-c
    SignalHelper::setShutDownSignal(SignalHelper::SIGTERM_); // shut down on killall

#if defined (STRINGIFY_H) && defined (STRING) && defined (TARGI)
    QString target = STRING(TARGI);
#else
    auto target=QStringLiteral("ApplicationNameString");
#endif

    QCoreApplication::setApplicationName(target);
    QCoreApplication::setApplicationVersion(Buildnumber::_value);
    QCoreApplication::setOrganizationName("horvathzoltan");
    QCoreApplication::setOrganizationDomain("https://github.com/horvathzoltan");

    QApplication a(argc, argv);

    _globals._helpers._sysinfoHelper.Init(target, Buildnumber::_value);
    QString sysInfo = _globals._helpers._sysinfoHelper.Get_SysInfo();
    qDebug()<<"started: " << sysInfo;

    // ha nincs meg a terminal mappa, akkor letrehozzuk
    if(!FileNameHelper::IsDirExists(FileNameHelper::terminalDirPath()))
    {
        QDir().mkdir(FileNameHelper::terminalDirPath());
    }

    // 1 ping
    // auto p1 = PingHelper::Ping_1(QHostAddress("192.168.1.254"), 5, 5);

    // több ping
    // QHostAddress hostAddress(_globals._helpers._sysinfoHelper.hostip());
    // auto p2 = PingHelper::Ping_Many(hostAddress, 5, 5);
    // QStringList p22 = p2.GetHosts();
    // QMap<QString,QSet<int>> p3 = NetworkHelper::FindHost_ByPorts(p22, {22,80});

    // QStringList p3txt = NetworkHelper::HostsByPorts_ToString(p3);
    // for(auto&pt:p3txt)
    // {
    //     qDebug()<<pt;
    // }

    MainWindow w;
    //bool localEcho;
    //SerialSettingsHelper::loadSettings(FileNameHelper::settingsPath(), _globals._serial, &localEcho);
    _globals._serialManager.loadSettings(FileNameHelper::settingsPath());
    //w.setLocalEcho(localEcho);
    //w.setStatusBarText(sysInfo);

    auto nix = _globals._helpers._sysinfoHelper.networkInterfaceIx();
    _globals._networkMonitor.setInterfaceIndex(nix);

    QObject::connect(&_globals._networkMonitor, &NetworkMonitor::ConnectedAction, &w, &MainWindow::onNetworkConnected);
    QObject::connect(&_globals._networkMonitor, &NetworkMonitor::DisconnectedAction, &w, &MainWindow::onNetworkDisconnected);
    QObject::connect(&_globals._networkMonitor, &NetworkMonitor::NoNetworkAction, &w, &MainWindow::onNoNetwork);

    _globals._networkMonitor.start();

    w.show();
    int r =  a.exec();
    //SerialSettingsHelper::saveSettings(FileNameHelper::settingsPath(), w.mSerial());
    return r;
}
