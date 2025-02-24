#include "fileerrors.h"
#include <QFileInfo>
#include <QDir>
#include <QDateTime>
#include <QIODevice>
#include <QChar>
#include <QDebug>

bool FnValidator::_verbose = false;

bool FnValidator::Validate_Load(const QString& filename, FileErrors *err)
{
    bool valid = Validate_Save(filename, err);

    if(!valid) return false;

    QFileInfo fi(filename);

    if(!fi.exists())
    {
        if(_verbose) qInfo()<<(QStringLiteral("file not exist: %1").arg(filename));
        if(err != nullptr) *err= FileErrors::FileNotExists;
        return false;
    }

    return true;
}

bool FnValidator::Validate_Save(const QString& filename, FileErrors *err)
{
    if(filename.isEmpty())
    {
        if(_verbose) qInfo()<<(QStringLiteral("no file name").arg(filename));
        if(err != nullptr) *err= FileErrors::NoFileName;
        return false;
    }

    if(filename.length()>256)
    {
        if(_verbose) qInfo()<<(QStringLiteral("filename too long: %1").arg(filename));
        if(err!=nullptr) *err = FileErrors::FileNameTooLong;
        return false;
    }

    QFileInfo fi(filename);

    if(!fi.isAbsolute())
    {
        if(_verbose) qInfo()<<(QStringLiteral("path is not absolute: %1").arg(filename));
        if(err != nullptr) *err= FileErrors::PathIsNotAbsolute;
        return false;
    }

    return true;
}



