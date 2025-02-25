#include <QApplication>
#include <QDebug>

#include <helpers/filenamehelper.h>
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
    qDebug()<<sysInfo;

    // ha nincs meg a terminal mappa, akkor letrehozzuk
    if(!FileNameHelper::IsDirExists(FileNameHelper::terminalDirPath()))
    {
        QDir().mkdir(FileNameHelper::terminalDirPath());
    }

    MainWindow w;
    bool localEcho;
    SerialSettingsHelper::loadSettings(FileNameHelper::settingsPath(), w.mSerial(), &localEcho);
    w.setLocalEcho(localEcho);

    w.show();
    int r =  a.exec();

    //SerialSettingsHelper::saveSettings(FileNameHelper::settingsPath(), w.mSerial());
    return r;
}
