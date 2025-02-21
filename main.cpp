#include <QApplication>
#include <QDebug>

#include "mainwindow.h"
#include "buildnumber.h"
#include "stringify.h"
#include "signalhelper.h"

#include "globals.h"

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

    auto homePath = _globals.homePath();
    qDebug()<<"homePath:"<<homePath;

    MainWindow w;
    w.show();
    return a.exec();
}
