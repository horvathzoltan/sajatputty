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

    static QString MSerial_ToString(QSerialPort *m_serial, bool localEcho);
};

#endif // SERIALSETTINGSHELPER_H
