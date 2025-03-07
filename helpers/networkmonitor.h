#ifndef NETWORKMONITOR_H
#define NETWORKMONITOR_H

#include "networkhelper.h"

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTimer>
#include <QDebug>
#include <QHostAddress>

class NetworkMonitor : public QObject {
    Q_OBJECT

private:
    enum Status{Unknown = -1, Connected, Disconnected, NoNetwork};

    QTimer _timer;
    bool _isStarted=false;
    int _interfaceIx=0;
    Status _lastStatus = Unknown;

public:
    NetworkMonitor(QObject *parent = nullptr) : QObject(parent){}

    void checkNetwork();

    void setInterfaceIndex(int v){_interfaceIx = v;}
    void start();
    void stop();

signals:
    void ConnectedAction();
    void DisconnectedAction();
    void NoNetworkAction();

};

#endif // NETWORKMONITOR_H
