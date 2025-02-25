#include "session.h"

#include <QFile>
#include <QTextStream>

#include <helpers/textfilehelper.h>

//#include <QFileDialog>


void SessionLog::saveSession(const QString& logfn, const QString& settingTxt, const QString& consoleTxt)
{
    //QString logfn = QFileDialog::getSaveFileName(this, tr("Save File"), "/home/pi/terminal_logs", tr(""));
    if(logfn.isNull() || logfn.isEmpty()) return;
    QFile logf(logfn);
    logf.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
    //stream = new QTextStream(logf);

    QTextStream stream(&logf);
    stream<<"Port name; Baud rate; Data bits; Parity bits; Stop bits; Flow control\n";
    stream<<settingTxt;
    for(int i = 0; i < _logd.length(); i++){
        auto logd = _logd.at(i);

        auto s = logd.wr()==SessionLog::Write?"TX":"RX";
        stream<<logd.timestamp().toString("yyyy.mm.dd@HH.mm.ss")<<" "
              <<s<<" "
              <<logd.data()<<"\n";
    }
    QFile logf2(logfn+".txt");
    logf2.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
    stream.setDevice(&logf2);
    stream<<consoleTxt;
    logf.close();
    logf2.close();
}

QString SessionLog::loadSession(const QString &logfn)
{
    QString txt =  TextFileHelper::Load(logfn, nullptr);
    return txt;
}
