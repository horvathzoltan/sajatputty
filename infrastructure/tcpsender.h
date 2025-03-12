#ifndef TCPSENDER_H
#define TCPSENDER_H

#include <QObject>
#include <QTcpSocket>


class TcpSender : public QObject {
    Q_OBJECT

public:
    TcpSender(QObject *parent = nullptr) : QObject(parent) {}

    bool initClient(const QString &host, int port);


private:
    QTcpSocket _socket;
    //QByteArray dataToSend;

// signals:
//     void send_signal(const QByteArray &);

private slots:
    void connected();
    void disconnected();
    void readyRead();
    void bytesWritten(qint64);
    void send_slot(const QByteArray &);
    void on_new_connection();

};
#endif // TCPSENDER_H
