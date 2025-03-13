#include "session.h"

#include <QFile>
#include <QTextStream>
#include <helpers/textfilehelper.h>
#include "infrastructure/logmode.h"


void SessionLog::saveSession(const QString& logfn, const QString& settingTxt)
{
    if(logfn.isNull()) return;
    if(logfn.isEmpty()) return;

    QFile logf(logfn);
    logf.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
    QTextStream stream(&logf);
    stream<<"portName;baudRate;dataBits;parityBits;stopBits;flowControl\n";
    stream<<settingTxt;    
    stream<<SerialData::ToString(_data, LogMode::Log);
    logf.flush();
    logf.close();
}

QString SessionLog::loadSession(const QString &logfn)
{
    QString txt =  TextFileHelper::Load(logfn, nullptr);
    return txt;
}

