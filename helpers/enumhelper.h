#ifndef ENUMHELPER_H
#define ENUMHELPER_H

#include "qmetaobject.h"
#include <QString>
#include <QSerialPort>


class EnumHelper
{
public:
    //EnumHelper();

    // static QString getParity(QSerialPort::Parity v);
    // static QString getBaudRate(int);
    // static QString getDataBits(int);
    // static QString getStopBits(int);
    // static QString getFlowControl(int);

    template<typename T>
    static QString ToString(T v){
        const char *a = QMetaEnum::fromType<T>().valueToKey(v);
        if(a == nullptr) return "Unknown";
        return QString(a);
    }
};

#endif // ENUMHELPER_H
