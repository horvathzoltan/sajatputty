#ifndef SERIALSETTINGSHELPER_H
#define SERIALSETTINGSHELPER_H

#include <QSerialPort>
#include <QString>

class SerialSettingsHelper
{
public:
    static QString MSerial_ToString(QSerialPort *m_serial);//, bool localEcho);

    static QString BaudRate_ToText(QSerialPort::BaudRate v);
    static QSerialPort::BaudRate To_BaudRate(const QString& v);

    static QString DataBits_ToText(QSerialPort::DataBits v);
    static QSerialPort::DataBits To_DataBits(const QString& v);

    static QString ParityBits_ToText(QSerialPort::Parity v);
    static QSerialPort::Parity To_ParityBits(const QString& v);

    static QString StopBits_ToText(QSerialPort::StopBits v);
    static QSerialPort::StopBits To_StopBits(const QString& v);

    static QString FlowControl_ToText(QSerialPort::FlowControl v);
    static QSerialPort::FlowControl To_FlowControl(const QString& v);

    static bool To_Bool(const QString& v);
};

#endif // SERIALSETTINGSHELPER_H
