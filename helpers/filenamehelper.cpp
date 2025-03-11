#include "filenamehelper.h"

FileNameHelper::FileNameHelper() {}

const QString FileNameHelper::_terminalDirName = "terminal";
//const QString FileNameHelper::_customSettingsDirName = "custom_settings";

const QString FileNameHelper::_logDirName = "terminal_logs";
const QString FileNameHelper::_logFileName = "log.txt";
const QString FileNameHelper::_serialSettingsFileName = "serial_settings.ini";
const QString FileNameHelper::_networkSettingsFileName = "network_settings.ini";

QString FileNameHelper::_homePath;

QString FileNameHelper::terminalDirPath()
{
    QDir d = QDir(_homePath);
    QString a =  d.filePath(_terminalDirName);
    return a;
}

QString FileNameHelper::logDirPath()
{
    return QDir(terminalDirPath()).filePath(_logDirName);
}

// QString FileNameHelper::customSettingsDirPath()
// {
//     return QDir(terminalDirPath()).filePath(_customSettingsDirName);
// }

QString FileNameHelper::serialSettingsFilePath()
{
    return QDir(terminalDirPath()).filePath(_serialSettingsFileName);
}

QString FileNameHelper::networkSettingsFilePath()
{
    return QDir(terminalDirPath()).filePath(_networkSettingsFileName);
}

bool FileNameHelper::IsFileExists(const QString &fn)
{
    QFileInfo check_file(fn);
    return check_file.exists() && check_file.isFile();
}

/**/
bool FileNameHelper::IsDirExists(const QString &fn)
{
    QFileInfo check_file(fn);
    return check_file.exists() && check_file.isDir();
}

/*terminaldir*/

bool FileNameHelper::IsTerminalDirExists()
{
    return IsDirExists(terminalDirPath());
}

void FileNameHelper::MakeTerminalDir()
{
    QDir().mkdir(FileNameHelper::terminalDirPath());
}

void FileNameHelper::Init(const QString &userName)
{
    _homePath = QDir::homePath();
    if(_homePath.isEmpty() || _homePath == "\\" || _homePath == "/")
    {
        _homePath = "/home/"+userName;
    }
}

/*custom*/

QString FileNameHelper::custom_serialSettingsFilePath()
{
    auto d = QDir(terminalDirPath());
    QString fn = generateUniqueFileName(d, _serialSettingsFileName);
    QString a = d.filePath(fn);
    return a;
}

QString FileNameHelper::custom_networkSettingsFilePath()
{
    auto d = QDir(terminalDirPath());
    QString fn = generateUniqueFileName(d, _networkSettingsFileName);
    QString a = d.filePath(fn);
    return a;
}

QString FileNameHelper::custom_logFilePath()
{
    auto d = QDir(terminalDirPath());
    QString fn = generateUniqueFileName(d, _logFileName);
    QString a = d.filePath(fn);
    return a;
}

QString FileNameHelper::generateUniqueFileName(const QDir &directory, const QString &fn)
{
    QFileInfo fi(fn);

    QString baseName = fi.baseName();// Base name for the file
    QString extension = fi.suffix(); // Extension for the file
    QString newFileName;
    int counter = 1;

    do {
        newFileName = baseName + '('+QString::number(counter)+")." + extension;
        counter++;
    } while (directory.exists(newFileName));

    return newFileName;
}
