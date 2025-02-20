QT += widgets serialport
requires(qtConfig(combobox))
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets core gui

TARGET = terminal
TEMPLATE = app

SOURCES += \
    enumhelper.cpp \
    main.cpp \
    mainwindow.cpp \
    settingsdialog.cpp \
    console.cpp \
    #ssd1306.cpp

HEADERS += \
    enumhelper.h \
    mainwindow.h \
    settingsdialog.h \
    console.h \
    #ssd1306.h

FORMS += \
    mainwindow.ui \
    settingsdialog.ui

RESOURCES += \
    terminal.qrc

INSTALLS += target

#LIBS+= -lwiringPi

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /home/pi/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
