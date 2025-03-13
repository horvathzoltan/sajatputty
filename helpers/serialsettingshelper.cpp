#include "enumhelper.h"
#include "serialsettingshelper.h"
#include <QDir>
#include <QSettings>
#include <helpers/filenamehelper.h>

QString SerialSettingsHelper::MSerial_ToString(QSerialPort *m_serial)
{
    auto e = m_serial->portName()+";"
           + QString::number(m_serial->baudRate())+";"
           + SerialSettingsHelper::DataBits_ToText(m_serial->dataBits())+";"
           + SerialSettingsHelper::StopBits_ToText(m_serial->stopBits())+";"
           + SerialSettingsHelper::ParityBits_ToText(m_serial->parity())+";"
             + SerialSettingsHelper::FlowControl_ToText(m_serial->flowControl())+"\n";
           //+ (localEcho?"enabled":"disabled")+"\n";

    return e;
}

QString SerialSettingsHelper::BaudRate_ToText(QSerialPort::BaudRate v)
{
    if(v == QSerialPort::Baud1200) return "1200";
    if(v == QSerialPort::Baud2400) return "2400";
    if(v == QSerialPort::Baud4800) return "4800";
    if(v == QSerialPort::Baud9600) return "9600";
    if(v == QSerialPort::Baud19200) return "19200";
    if(v == QSerialPort::Baud38400) return "38400";
    if(v == QSerialPort::Baud57600) return "57600";
    if(v == QSerialPort::Baud115200) return "115200";
    return "unknown";
}

QSerialPort::BaudRate SerialSettingsHelper::To_BaudRate(const QString &v)
{
    if(v == "1200") return QSerialPort::Baud1200;
    if(v == "2400") return QSerialPort::Baud2400;
    if(v == "4800") return QSerialPort::Baud4800;
    if(v == "9600") return QSerialPort::Baud9600;
    if(v == "19200") return QSerialPort::Baud19200;
    if(v == "38400") return QSerialPort::Baud38400;
    if(v == "57600") return QSerialPort::Baud57600;
    if(v == "115200") return QSerialPort::Baud115200;
    return QSerialPort::UnknownBaud;
}

/**/

QString SerialSettingsHelper::DataBits_ToText(QSerialPort::DataBits v)
{
    if(v == QSerialPort::Data5) return "5";
    if(v == QSerialPort::Data6) return "6";
    if(v == QSerialPort::Data7) return "7";
    if(v == QSerialPort::Data8) return "8";
    return "unknown";
}

QSerialPort::DataBits SerialSettingsHelper::To_DataBits(const QString &v)
{
    if(v == "5") return QSerialPort::Data5;
    if(v == "6") return QSerialPort::Data6;
    if(v == "7") return QSerialPort::Data7;
    if(v == "8") return QSerialPort::Data8;
    return QSerialPort::UnknownDataBits;
}

/**/

QString SerialSettingsHelper::ParityBits_ToText(QSerialPort::Parity v)
{
    if(v == QSerialPort::NoParity) return "None";
    if(v == QSerialPort::EvenParity) return "Even";
    if(v == QSerialPort::OddParity) return "Odd";
    if(v == QSerialPort::MarkParity) return "Mark";
    if(v == QSerialPort::SpaceParity) return "Space";
    return "unknown";
}

QSerialPort::Parity SerialSettingsHelper::To_ParityBits(const QString &v)
{
    if(v == "None") return QSerialPort::NoParity;
    if(v == "Even") return QSerialPort::EvenParity;
    if(v == "Odd") return QSerialPort::OddParity;
    if(v == "Mark") return QSerialPort::MarkParity;
    if(v == "Space") return QSerialPort::SpaceParity;
    return QSerialPort::UnknownParity;
}

/**/

QString SerialSettingsHelper::StopBits_ToText(QSerialPort::StopBits v)
{
    if(v == QSerialPort::OneStop) return "1";
    if(v == QSerialPort::OneAndHalfStop) return "1.5";
    if(v == QSerialPort::TwoStop) return "2";
    return "unknown";
}

QSerialPort::StopBits SerialSettingsHelper::To_StopBits(const QString &v)
{
    if(v == "1") return QSerialPort::OneStop;
    if(v == "1.5") return QSerialPort::OneAndHalfStop;
    if(v == "2") return QSerialPort::TwoStop;
    return QSerialPort::UnknownStopBits;
}

/**/

QString SerialSettingsHelper::FlowControl_ToText(QSerialPort::FlowControl v)
{
    if(v == QSerialPort::NoFlowControl) return "None";
    if(v == QSerialPort::HardwareControl) return "RTS/CTS";
    if(v == QSerialPort::SoftwareControl) return "XON/XOFF";
    return "unknown";
}

QSerialPort::FlowControl SerialSettingsHelper::To_FlowControl(const QString &v)
{
    if(v == "None") return QSerialPort::NoFlowControl;
    if(v == "RTS/CTS") return QSerialPort::HardwareControl;
    if(v == "XON/XOFF") return QSerialPort::SoftwareControl;
    return QSerialPort::UnknownFlowControl;
}

bool SerialSettingsHelper::To_Bool(const QString &v)
{
    QString b = v.toLower();
    if(b=="enabled") return true;
    if(b=="ok") return true;
    if(b=="true") return true;
    if(b=="on") return true;
    if(b=="1") return true;

    return false;
}


