#ifndef SERIALSETTINGSVM_H
#define SERIALSETTINGSVM_H

#include <QSerialPort>


struct SerialSettingsVM {
    QString portName;
    QSerialPort::BaudRate baudRate;        
    QSerialPort::DataBits dataBits;
    QSerialPort::StopBits stopBits;
    QSerialPort::Parity parity;
    QSerialPort::FlowControl flowControl;
    bool localEchoEnabled;
};

#endif // SERIALSETTINGSVM_H
