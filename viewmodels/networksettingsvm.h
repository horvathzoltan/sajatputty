#ifndef NETWORKSETTINGSVM_H
#define NETWORKSETTINGSVM_H

#include <QString>


struct NetworkSettingsVM {
    QString deviceIp;
    QString serverIp;
    int serverPort;
    QString messageTemplate;
};

#endif // NETWORKSETTINGSVM_H
