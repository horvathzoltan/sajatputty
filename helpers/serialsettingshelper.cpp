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
    return m_serial->portName()+";"
           + QString::number(m_serial->baudRate())+";"
           + EnumHelper::ToString(m_serial->dataBits())+";"
           + EnumHelper::ToString(m_serial->parity())+";"
           + EnumHelper::ToString(m_serial->stopBits())+";"
           + EnumHelper::ToString(m_serial->flowControl())+";"
           + (localEcho?"enabled":"disabled")+"\n";
}

/*
void Settings::loadSettings()
{
    if(_settingsFn.isNull() || _settingsFn.isEmpty()){
        QDir d("/home/pi/terminal_settings");
        auto list = d.entryList(QDir::NoFilter, QDir::Time);
        if(list.isEmpty()) return;

        _settingsFn = list.at(1);
        if(_settingsFn.isNull() || _settingsFn.isEmpty()) return;
        _settingsFn = "/home/pi/terminal_settings/" + _settingsFn;

    }
    QSettings settings(_settingsFn, QSettings::NativeFormat);
    m_serial->setPortName(settings.value("name").toString());
    m_serial->setBaudRate(settings.value("bR").toInt());
    m_serial->setDataBits(settings.value("dB").value<QSerialPort::DataBits>());
    m_serial->setStopBits(settings.value("sB").value<QSerialPort::StopBits>());
    m_serial->setParity(settings.value("par").value<QSerialPort::Parity>());
    m_serial->setFlowControl(settings.value("fC").value<QSerialPort::FlowControl>());

    SettingsDialog::Settings p;
    p.name = m_serial->portName();

    qint32 baudRate_int = m_serial->baudRate();
    QSerialPort::BaudRate baudRate = static_cast<QSerialPort::BaudRate>(baudRate_int);
    p.baudRate = baudRate;

    p.dataBits = m_serial->dataBits();
    p.parity = m_serial->parity();
    p.stopBits = m_serial->stopBits();
    p.flowControl = m_serial->flowControl();
    p.localEchoEnabled = false;
    m_settings->setSettings(p);
}

void Settings::saveSettings()
{
    _settingsFn = "/home/pi/terminal_settings/" + logfn.split('/').last();
    QSettings settings(_settingsFn, QSettings::NativeFormat);
    QString name = m_serial->portName();
    qint32 bR = m_serial->baudRate();
    QSerialPort::DataBits dB = m_serial->dataBits();
    QSerialPort::StopBits sB = m_serial->stopBits();
    QSerialPort::Parity par = m_serial->parity();
    QSerialPort::FlowControl fC = m_serial->flowControl();
    settings.setValue("bR", bR);
    settings.setValue("dB", dB);
    settings.setValue("sB", sB);
    settings.setValue("par", par);
    settings.setValue("fC", fC);
    settings.setValue("name", name);
}
 */
