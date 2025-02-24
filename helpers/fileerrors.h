#ifndef COM_ZFILEERROR_H
#define COM_ZFILEERROR_H

#include <QFile>
#include <QFileInfo>
#include <QString>
#include <QTextStream>

enum FileErrors:int{
    Ok = 0,
    NoFileName,
    PathIsNotAbsolute,
    FileNotExists,
    CannotRead,
    CannotWrite, FileNameTooLong
};
class FnValidator
{
private:
    static bool _verbose;
public:

    void SetVerbose(bool v){ _verbose = v;}

public:
    static bool Validate_Load(const QString& filename, FileErrors *err);
    static bool Validate_Save(const QString& filename, FileErrors *err);
};


#endif // ZTEXTFILEHELPER_H
