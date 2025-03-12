#include "tcpsender.h"

#include <QTcpSocket>
#include <QDebug>

TcpSender::TcpSender(QObject *parent) : QObject(parent)
{
    connect(&_socket, &QTcpSocket::connected, this, &TcpSender::connected);
    connect(&_socket, &QTcpSocket::disconnected, this, &TcpSender::disconnected);
    connect(&_socket, &QTcpSocket::bytesWritten, this, &TcpSender::bytesWritten);
    connect(&_socket, &QTcpSocket::errorOccurred, this, &TcpSender::onError);
}

bool TcpSender::Init(const QString &host, int port)
{
    _host = host;
    _port = port;

    return true;
}

void TcpSender::connected()
{
    send_buffer();
}

void TcpSender::disconnected()
{
   _socket.close();
}

void TcpSender::onError(QTcpSocket::SocketError socketError)
{
    qDebug() << "Socket error:" << socketError;
     _socket.close();
}

void TcpSender::bytesWritten(qint64 bytes)
{
    _buffer.removeFirst(bytes);
}

void TcpSender::send_buffer()
{
    auto a = _buffer.get();
    if(!a.isEmpty())
    {
        _socket.write(a);
    }
}

void TcpSender::send(const QByteArray &msg){
    _buffer.append(msg);

    if(_socket.state() == QAbstractSocket::ConnectedState){
        send_buffer();
    } else if(_socket.state() == QAbstractSocket::UnconnectedState) {
        _socket.connectToHost(_host, static_cast<quint16>(_port));
    }
}

void TcpSender::Disconnect(){
    _socket.disconnectFromHost();
}
