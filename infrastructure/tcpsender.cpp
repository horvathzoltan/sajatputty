#include "tcpsender.h"

#include <QTcpSocket>
#include <QDebug>



bool TcpSender::initClient(const QString &host, int port)
{
    //connect(this, &TcpSender::send_signal, this, &TcpSender::send_slot);
    connect(&_socket, &QTcpSocket::connected, this, &TcpSender::connected);
    connect(&_socket, &QTcpSocket::disconnected, this, &TcpSender::disconnected);
    connect(&_socket, &QTcpSocket::bytesWritten, this, &TcpSender::bytesWritten);

    _socket.connectToHost(host, static_cast<quint16>(port));

    if(!_socket.waitForConnected(5000)){
        qDebug()<< QStringLiteral("Could not connect to TCP socket: %1:%2").arg(host).arg(QString::number(port));
        return false;
    }

    return true;
}



void TcpSender::connected()
{
    //LogHelper::inf(QStringLiteral("Succesfully connected to TCP socket"));
}

void TcpSender::disconnected()
{
    //LogHelper::inf(QStringLiteral("Disconnected from TCP socket"));
}


void TcpSender::bytesWritten(qint64 bytes)
{
    //LogHelper::inf(QString::number( bytes)+ " bytes written");
}

void TcpSender::send_slot(const QByteArray &msg)
{
    auto sent = _socket.write(msg);
    if(sent < 0 || sent < msg.length()){
        qDebug()<<QStringLiteral("Could not write %1 bytes out of %2 to TCP socket \n\tmsg:").arg(QString::number(msg.length() - sent)).arg(QString::number(msg.length()))
                 <<("\t" + msg, 0);
    }
}
