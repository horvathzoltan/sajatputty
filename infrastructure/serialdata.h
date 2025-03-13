#include <QBrush>
#include <QDateTime>
#include <QString>

#ifndef SERIALDATATYPE_H
#define SERIALDATATYPE_H

struct SerialData{
public:
    enum Type{ RX, TX, Comment, Unknown };

    static const QBrush commentBrush;

private:
    QDateTime _timeStamp;
    Type _type;
    QByteArray _data;

public:
    SerialData(SerialData::Type wr, const QByteArray& data);

    QDateTime timestamp() const{return _timeStamp;}
    QString timestampStr() const{return _timeStamp.toString("yyyy.MM.ddTHH:mm:ss.zzz");}
    Type type() const{return _type;}
    QString typeStr() const;

    QByteArray data() const{return _data;}

    QBrush brush() const;

    static QString ToString(const QList<SerialData>& data);
};

#endif // SERIALDATATYPE_H
