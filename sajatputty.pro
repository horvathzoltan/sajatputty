QT += widgets serialport network

requires(qtConfig(combobox))
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets core gui

TARGET = SerialTerminal
TEMPLATE = app

DEFINES += TARGI=$$TARGET
message( "TARGET = "$$TARGET )

SOURCES += \
    helpers/enumhelper.cpp \
    helpers/fileerrors.cpp \
    helpers/filenamehelper.cpp \
    helpers/networkhelper.cpp \
    helpers/networkmonitor.cpp \
    helpers/pinghelper.cpp \
    helpers/processhelper.cpp \
    helpers/serialsettingshelper.cpp \
    helpers/signalhelper.cpp \
    helpers/sysinfohelper.cpp \
    helpers/textfilehelper.cpp \
    infrastructure/buildnumber.cpp \
    infrastructure/globals.cpp \
    infrastructure/networkmanager.cpp \
    infrastructure/serialmanager.cpp \
    infrastructure/tcpsender.cpp \
    main.cpp \
    mainwindow.cpp \
    session.cpp \
    settingsdialog.cpp \
    console.cpp \
    settingsnetworkdialog.cpp
     #ssd1306.cpp

HEADERS += \
    helpers/enumhelper.h \
    helpers/fileerrors.h \
    helpers/filenamehelper.h \
    helpers/networkhelper.h \
    helpers/networkmonitor.h \
    helpers/pinghelper.h \
    helpers/processhelper.h \
    helpers/serialsettingshelper.h \
    helpers/signalhelper.h \
    helpers/stringify.h \
    helpers/sysinfohelper.h \
    helpers/textfilehelper.h \
    infrastructure/buildnumber.h \
    infrastructure/globals.h \
    infrastructure/networkmanager.h \
    infrastructure/serialmanager.h \
    infrastructure/tcpsender.h \
    mainwindow.h \
    session.h \
    settingsdialog.h \
    console.h \
    settingsnetworkdialog.h \
    viewmodels/networksettingsvm.h \
    viewmodels/serialsettingsvm.h
     #ssd1306.h

FORMS += \
    mainwindow.ui \
    settingsdialog.ui \
    settingsnetworkdialog.ui

RESOURCES += \
    terminal.qrc

INSTALLS += target

contains(QMAKESPEC,.*linux-rasp-pi\d*-.*){
    message(rpi)
    CONFIG += rpi
    DEFINES += RASPBERRY_PI
}

unix:rpi:{
message(LIBS added for raspberry_pi)
#LIBS += -lwiringPi
#LIBS += -lnfc -lpthread
#LIBS += -lusb-1.0
}

#LIBS+= -lwiringPi

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /home/pi/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
