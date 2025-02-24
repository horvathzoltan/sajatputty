#include "filenamehelper.h"

FileNameHelper::FileNameHelper() {}

const QString FileNameHelper::_terminalDirName = "terminal";
const QString FileNameHelper::_logDirName = "terminal_logs";
const QString FileNameHelper::_logFileName = "terminal_log.txt";
const QString FileNameHelper::_settingsFileName = "terminal_settings.txt";
const QString FileNameHelper::_homePath = QDir::homePath();

QString FileNameHelper::terminalDirPath()
{
    return QDir(_homePath).filePath(_terminalDirName);
}

QString FileNameHelper::terminalLogPath()
{
    return QDir(terminalDirPath()).filePath(_logFileName);
}

QString FileNameHelper::settingsPath()
{
    return QDir(terminalDirPath()).filePath(_settingsFileName);
}

bool FileNameHelper::IsFileExists(const QString &fn)
{
    QFileInfo check_file(fn);
    return check_file.exists() && check_file.isFile();
}

bool FileNameHelper::IsDirExists(const QString &fn)
{
    QFileInfo check_file(fn);
    return check_file.exists() && check_file.isDir();
}
