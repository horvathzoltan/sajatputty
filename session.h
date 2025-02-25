#ifndef SESSION_H
#define SESSION_H

#include <QDateTime>
#include <QList>
#include <QString>

class SessionLog
{
public:
    enum LogType:int{ Write=1, Read=2 };
    struct Data{
    private:
        QDateTime _timestamp;
        LogType _wr;
        QByteArray _data;

    public:
        Data(LogType wr, const QByteArray& data)
        {
            _timestamp = QDateTime::currentDateTime();
            _wr = wr;
            _data = data;
        }

        QDateTime timestamp() const{return _timestamp;}
        LogType wr() const{return _wr;}
        QByteArray data() const{return _data;}
    };

private:
    QList<struct Data> _logd;// = nullptr;
public:
    void saveSession(const QString& logfn, const QString& settingTxt, const QString& consoleTxt);
    QString loadSession(const QString& logfn);
    void clear(){_logd.clear();}
    void append(Data a){_logd.append(a);}
};

#endif // SESSION_H
