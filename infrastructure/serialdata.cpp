#include "serialdata.h"

const QBrush SerialData::commentBrush = QBrush((Qt::GlobalColor)Qt::cyan);

SerialData::SerialData(Type wr, const QByteArray &data)
{
    _timeStamp = QDateTime::currentDateTime();
    _type = wr;
    _data = data;
}

QString SerialData::typeStr() const{
    if(_type == SerialData::Type::RX ) return QStringLiteral("RX");
    if(_type ==  SerialData::Type::TX) return QStringLiteral("TX");
    return {};
}

QBrush SerialData::brush() const
{
    static QBrush yellow = QBrush((Qt::GlobalColor)Qt::yellow);
    static QBrush green = QBrush((Qt::GlobalColor)Qt::green);
    static QBrush gray = QBrush((Qt::GlobalColor)Qt::gray);

    if(_type == TX) return yellow;
    if(_type == RX) return green;
    if(_type == Comment) return commentBrush;
    return gray;
}

QString SerialData::ToString(const QList<SerialData> &data, LogMode logMode)
{
    auto prevType = SerialData::Type::Unknown;
    QString row;

    for(auto&d:data)
    {
        if(logMode == LogMode::Log)
        {
            if(d.type() != prevType)
            {
                if(!row.isEmpty()) row+='\n';
                row+=d.timestampStr()+','+d.typeStr()+','+d.data();
                prevType = d.type();
            } else{
                row+=d.data();
            }
        } else{
            row+=d.data();
        }
    }
    return row;
}
