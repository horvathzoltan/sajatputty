#include "networkmonitor.h"



void NetworkMonitor::checkNetwork()
{
    if(_interfaceIx != 0)
    {
        bool isConnected = NetworkHelper::isConnected_ByInterfaceIndex(_interfaceIx);


        if(isConnected)
        {
            if(_lastStatus != Connected)
            {
                _lastStatus = Connected;
                emit ConnectedAction();
            }
        }
        else
        {
            if(_lastStatus != Disconnected)
            {
                _lastStatus = Disconnected;
                emit DisconnectedAction();
            }
        }
    }
    else
    {
        //if(_lastStatus != NoNetwork)
       // {
         //   _lastStatus = NoNetwork;
            emit NoNetworkAction();
       // }
    }

    if(_isStarted)
    {
        QTimer::singleShot(5000, this, &NetworkMonitor::checkNetwork); // Check every 5 seconds
    }
}

void NetworkMonitor::start()
{
    if(_isStarted) return;
    _isStarted = true;
    checkNetwork();
}

void NetworkMonitor::stop()
{
    _isStarted = false;
}
