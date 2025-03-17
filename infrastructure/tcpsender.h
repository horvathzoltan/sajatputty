#ifndef TCPSENDER_H
#define TCPSENDER_H

#include <QObject>
#include <QTcpSocket>

#include <QByteArray>
#include <QMutex>
#include <QMutexLocker>
#include "infrastructure/serialdata.h"
#include "threadsafearray.h"


class TcpSender : public QObject {
    Q_OBJECT

public:        
    TcpSender(QObject *parent = nullptr);
    bool Init(const QString &host, int port);
    void Disconnect();
    void send(const SerialData &, LogMode mode, const QString& deviceTag);

private:
    QTcpSocket _socket;
    QString _host;
    int _port;
    ThreadSafeArray<SerialData> _buffer;
    void send_buffer();
    LogMode _mode;
    QString _deviceTag;

private slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64);
    void onError(QTcpSocket::SocketError socketError);
};
#endif // TCPSENDER_H
