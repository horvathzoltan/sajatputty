#ifndef SERIALSETTINGSHELPER_H
#define SERIALSETTINGSHELPER_H

#include <QSerialPort>
#include <QString>

class SerialSettingsHelper
{
private:
public:
    SerialSettingsHelper();
    static void loadSettings(const QString& fn, QSerialPort *m_serial, bool* localEcho);
    static void saveSettings(const QString& fn, QSerialPort *m_serial, bool localEcho);

    static QString MSerial_ToString(QSerialPort *m_serial);//, bool localEcho);


    static QString BaudToText(QSerialPort::BaudRate v);
    static QString DataBitsToText(QSerialPort::DataBits v);
    static QString ParityToText(QSerialPort::Parity v);
    static QString StopBitsToText(QSerialPort::StopBits v);
    static QString FlowControlToText(QSerialPort::FlowControl v);
};

#endif // SERIALSETTINGSHELPER_H
