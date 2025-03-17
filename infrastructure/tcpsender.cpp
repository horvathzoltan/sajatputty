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
    int rows = 0;
    _buffer.removeFirst(rows);
}

void TcpSender::send_buffer()
{
    QList<SerialData> a = _buffer.get();
    QByteArray msg = SerialData::ToString(a, _mode).toLocal8Bit();

    if(!_deviceTag.isEmpty())
    {
        msg.prepend(_deviceTag.toLocal8Bit()+',');
    }

    if (!a.isEmpty())
    {
        qint64 sent = _socket.write(msg);
        if(sent == msg.length())
        {
            _buffer.removeFirst(a.length());
        }
    }
}

void TcpSender::send(const SerialData &d, LogMode mode, const QString& tag)
{
    _mode = mode;
    _deviceTag = tag;
    _buffer.append(d);

    if(_socket.state() == QAbstractSocket::ConnectedState){
        send_buffer();
    } else if(_socket.state() == QAbstractSocket::UnconnectedState) {
        _socket.connectToHost(_host, static_cast<quint16>(_port));
    }
}

void TcpSender::Disconnect(){
    _socket.disconnectFromHost();
}
