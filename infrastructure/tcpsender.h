#ifndef TCPSENDER_H
#define TCPSENDER_H

#include <QObject>
#include <QTcpSocket>

#include <QByteArray>
#include <QMutex>
#include <QMutexLocker>
#include "infrastructure/serialdata.h"


template<typename T>
class ThreadSafeArray {
public:

    ThreadSafeArray() = default;

    // Append data to the QByteArray
    void append(const T& data) {
        QMutexLocker locker(&mutex); // Lock the mutex for thread-safe access
        _data.append(data);
    }

    // Retrieve and remove data from the QByteArray
    QList<T> get() {
        QMutexLocker locker(&mutex); // Lock the mutex for thread-safe access
        return _data;
    }

    void removeFirst(qint64 len){
        QMutexLocker locker(&mutex); // Lock to safely access size
        //_data.removeAt(0, len);
        _data.erase(_data.begin(), _data.begin() + len);
    }


private:
    QList<T> _data;
    QMutex mutex;
};

class TcpSender : public QObject {
    Q_OBJECT

public:        
    TcpSender(QObject *parent = nullptr);
    bool Init(const QString &host, int port, LogMode m);
    void Disconnect();
    void send(const SerialData &);

private:
    QTcpSocket _socket;
    QString _host;
    int _port;
    ThreadSafeArray<SerialData> _buffer;

    LogMode _mode;

    void send_buffer();


private slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64);
    void onError(QTcpSocket::SocketError socketError);
};
#endif // TCPSENDER_H
