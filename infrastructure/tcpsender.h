#ifndef TCPSENDER_H
#define TCPSENDER_H

#include <QObject>
#include <QTcpSocket>

#include <QByteArray>
#include <QMutex>
#include <QMutexLocker>

class ThreadSafeByteArray {
public:
    ThreadSafeByteArray() {}

    // Append data to the QByteArray
    void append(const QByteArray &data) {
        QMutexLocker locker(&mutex); // Lock the mutex for thread-safe access
        byteArray.append(data);
    }

    // void append(const char *data, int len) {
    //     QMutexLocker locker(&mutex); // Overloaded for raw data
    //     byteArray.append(data, len);
    // }

    // Retrieve and remove data from the QByteArray
    QByteArray get() {
         QMutexLocker locker(&mutex); // Lock the mutex for thread-safe access
        // if (len > byteArray.size()) {
        //     len = byteArray.size(); // Adjust length to available data
        // }

        QByteArray result(byteArray);
        //byteArray.remove(0, len); // Remove retrieved data
        return result;
    }

    // Get the current size of the QByteArray
    // int size() {
    //     QMutexLocker locker(&mutex); // Lock to safely access size
    //     return byteArray.size();
    // }

    void removeFirst(qint64 len){
        QMutexLocker locker(&mutex); // Lock to safely access size
        byteArray.remove(0, len);
    }

    // bool isEmpty(){
    //     QMutexLocker locker(&mutex); // Lock to safely access size
    //     return byteArray.isEmpty();
    // }



private:
    QByteArray byteArray;
    QMutex mutex;
};

class TcpSender : public QObject {
    Q_OBJECT

public:

    TcpSender(QObject *parent = nullptr);
    bool Init(const QString &host, int port);
    void send(const QByteArray &);
    void Disconnect();

private:
    QTcpSocket _socket;
    QString _host;
    int _port;
    ThreadSafeByteArray _buffer;

    void send_buffer();


private slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64);
    void onError(QTcpSocket::SocketError socketError);
};
#endif // TCPSENDER_H
