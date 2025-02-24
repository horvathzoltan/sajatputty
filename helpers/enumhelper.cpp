#include "enumhelper.h"
#include "qmetaobject.h"

// EnumHelper::EnumHelper()
// {

// }

// QString EnumHelper::getParity(QSerialPort::Parity p)
// {
//     const char *a = QMetaEnum::fromType<QSerialPort::Parity>().valueToKey(p);
//     if(a == nullptr) return "Unknown";
//     return QString(a);
//     // switch(p){
//     // case 0: return "None";
//     // case 2: return "Even";
//     // case 3: return "Odd";
//     // case 4: return "Space";
//     // case 5: return "Mark";
//     // case -1: return "Unknown";
//     // default: return "Unknown";
//     // }
// }

// QString EnumHelper::getBaudRate(int b)
// {
//     switch(b){
//     case 1200: return "1200";
//     case 2400: return "2400";
//     case 4800: return "4800";
//     case 9600: return "9600";
//     case 19200: return "19200";
//     case 38400: return "38400";
//     case 57600: return "57600";
//     case 115200: return "115200";
//     case -1: return "Unknown";
//     default: return "Unknown";
//     }
// }

// QString EnumHelper::getDataBits(int d)
// {
//     switch(d){
//     case 5: return "5";
//     case 6: return "6";
//     case 7: return "7";
//     case 8: return "8";
//     case -1: return "Unknown";
//     default: return "Unknown";
//     }
// }

// QString EnumHelper::getStopBits(int s)
// {
//     switch (s){
//     case 1: return "1";
//     case 2: return "2";
//     case 3: return "1.5";
//     case -1: return "Unknown";
//     default: return "Unknown";
//     }
// }

// QString EnumHelper::getFlowControl(int f)
// {
//     switch(f){
//     case 0: return "None";
//     case 1: return "RTS/CTS";
//     case 2: return "XON/XOFF";
//     case -1: return "Unknown";
//     default: return "Unknown";
//     }
// }
