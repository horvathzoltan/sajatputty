#ifndef SESSION_H
#define SESSION_H

#include "infrastructure/serialdata.h"
#include <QDateTime>
#include <QList>
#include <QString>

class SessionLog
{
public:    
    // struct Data{
    // private:
    //     QDateTime _timestamp;
    //     SerialDataType _type;
    //     QByteArray _data;

    // public:
    //     Data(SerialDataType wr, const QByteArray& data)
    //     {
    //         _timestamp = QDateTime::currentDateTime();
    //         _type = wr;
    //         _data = data;
    //     }

    //     QDateTime timestamp() const{return _timestamp;}
    //     QString timestampStr() const{return _timestamp.toString("yyyy.MM.ddTHH:mm:ss.zzz");}
    //     SerialDataType type() const{return _type;}
    //     QString typeStr() const;
    //     QByteArray data() const{return _data;}
    // };

private:
    QList<SerialData> _data;// = nullptr

    //QString ToString();
public:
    void saveSession(const QString& logfn, const QString& settingTxt);
    QString loadSession(const QString& logfn);
    void clear(){_data.clear();}
    void append(SerialData a){_data.append(a);}
};

#endif // SESSION_H
