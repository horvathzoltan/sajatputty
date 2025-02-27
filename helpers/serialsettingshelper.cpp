#include "enumhelper.h"
#include "serialsettingshelper.h"
#include <QDir>
#include <QSettings>
#include <helpers/filenamehelper.h>


SerialSettingsHelper::SerialSettingsHelper() {}

void SerialSettingsHelper::loadSettings(const QString& _settingsFn,QSerialPort *m_serial, bool* localEcho)
{
    if(_settingsFn.isEmpty()) return;
    if(!FileNameHelper::IsFileExists(_settingsFn)) return;
    if(!m_serial) return;
    if(!localEcho) return;

    QSettings settings(_settingsFn, QSettings::NativeFormat);
    m_serial->setPortName(settings.value("name").toString());
    m_serial->setBaudRate(settings.value("bR").toInt());
    m_serial->setDataBits(settings.value("dB").value<QSerialPort::DataBits>());
    m_serial->setStopBits(settings.value("sB").value<QSerialPort::StopBits>());
    m_serial->setParity(settings.value("par").value<QSerialPort::Parity>());
    m_serial->setFlowControl(settings.value("fC").value<QSerialPort::FlowControl>());

    *localEcho = settings.value("localEcho").toBool();
}

void SerialSettingsHelper::saveSettings(const QString& _settingsFn, QSerialPort *m_serial, bool localEcho)
{    
    if(_settingsFn.isEmpty()) return;
    if(!m_serial) return;

    //_settingsFn = "/home/pi/terminal_settings/" + logfn.split('/').last();
    QSettings settings(_settingsFn, QSettings::NativeFormat);
    settings.setValue("bR", m_serial->baudRate());
    settings.setValue("dB", m_serial->dataBits());
    settings.setValue("sB", m_serial->stopBits());
    settings.setValue("par", m_serial->parity());
    settings.setValue("fC", m_serial->flowControl());
    QString name = m_serial->portName();
    settings.setValue("name", name);
    //QString localEcho_txt = localEcho ? "enabled" : "disabled";;
    settings.setValue("localEcho", localEcho);
}

QString SerialSettingsHelper::MSerial_ToString(QSerialPort *m_serial, bool localEcho)
{
    auto e = m_serial->portName()+";"
           + QString::number(m_serial->baudRate())+";"
           + SerialSettingsHelper::DataBitsToText(m_serial->dataBits())+";"
           + SerialSettingsHelper::StopBitsToText(m_serial->stopBits())+";"
           + SerialSettingsHelper::ParityToText(m_serial->parity())+";"
           + SerialSettingsHelper::FlowControlToText(m_serial->flowControl())+";"
           + (localEcho?"enabled":"disabled")+"\n";

    return e;
}

QString SerialSettingsHelper::BaudToText(QSerialPort::BaudRate v)
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

QString SerialSettingsHelper::DataBitsToText(QSerialPort::DataBits v)
{
    if(v == QSerialPort::Data5) return "5";
    if(v == QSerialPort::Data6) return "6";
    if(v == QSerialPort::Data7) return "7";
    if(v == QSerialPort::Data8) return "8";
    return "unknown";
}

QString SerialSettingsHelper::ParityToText(QSerialPort::Parity v)
{
    if(v == QSerialPort::NoParity) return "None";
    if(v == QSerialPort::EvenParity) return "even";
    if(v == QSerialPort::OddParity) return "Odd";
    if(v == QSerialPort::MarkParity) return "Mark";
    if(v == QSerialPort::SpaceParity) return "Space";
    return "unknown";
}

QString SerialSettingsHelper::StopBitsToText(QSerialPort::StopBits v)
{
    if(v == QSerialPort::OneStop) return "1";
    if(v == QSerialPort::OneAndHalfStop) return "1.5";
    if(v == QSerialPort::TwoStop) return "2";
    return "unknown";
}

QString SerialSettingsHelper::FlowControlToText(QSerialPort::FlowControl v)
{
    if(v == QSerialPort::NoFlowControl) return "None";
    if(v == QSerialPort::HardwareControl) return "RTS/CTS";
    if(v == QSerialPort::SoftwareControl) return "XON/XOFF";
    return "unknown";
}
