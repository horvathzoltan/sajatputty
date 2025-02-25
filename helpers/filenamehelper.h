#ifndef FILENAMEHELPER_H
#define FILENAMEHELPER_H

#include <QString>
#include <QDir>
#include <QFileInfo>

class FileNameHelper
{
public:
    FileNameHelper();

private:
    static const QString _terminalDirName;// = "terminal";
    static const QString _logDirName;// = "terminal_logs";
    static const QString _logFileName;// = "terminal_log.txt";
    static const QString _settingsFileName;// = "terminal_settings.txt";
    static const QString _homePath;// = QDir::homePath();

public:
    static QString terminalDirPath();
    static QString terminalLogPath();
    static QString settingsPath();

    static bool IsFileExists(const QString& fn);
    static bool IsDirExists(const QString& fn);
};

#endif // FILENAMEHELPER_H
