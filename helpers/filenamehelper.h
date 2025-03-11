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
//    static const QString _customSettingsDirName;
    static const QString _logDirName;// = "terminal_logs";
    static const QString _logFileName;// = "terminal_log.txt";
    static const QString _serialSettingsFileName;// = "terminal_settings.txt";
    static const QString _networkSettingsFileName;// = "terminal_settings.txt";
    static QString _homePath;// = QDir::homePath();

    //static QString terminalDirPath();
    //static QString customSettingsDirPath();
    static QString generateUniqueFileName(const QDir& dir, const QString& fn);
public:

    static QString terminalDirPath();

    static QString serialSettingsFilePath();
    static QString networkSettingsFilePath();
    static QString logDirPath();

    static QString custom_serialSettingsFilePath();
    static QString custom_networkSettingsFilePath();
    static QString custom_logFilePath();

    static bool IsFileExists(const QString& fn);
    static bool IsDirExists(const QString& fn);

    static bool IsTerminalDirExists();
    static void MakeTerminalDir();
    static void Init(const QString& userName);
};

#endif // FILENAMEHELPER_H
