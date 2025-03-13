#ifndef NETWORKSETTINGSVM_H
#define NETWORKSETTINGSVM_H

#include "infrastructure/logmode.h"
#include "infrastructure/chanelmode.h"
#include <QString>


struct NetworkSettingsVM {
    QString deviceTag;
    QString deviceIp;
    QString serverIp;
    int serverPort;
    QString messageTemplate;

    LogMode logMode;
    ChanelMode chanelMode;
};

#endif // NETWORKSETTINGSVM_H
