#ifndef FILEUTILS_MACOS_H
#define FILEUTILS_MACOS_H

#include <QtGlobal>

#ifdef Q_OS_OSX

#include <QObject>
#include<QDebug>

#define FILE_UTILS_PREFIX_MACOS "/Contents/MacOS/"
#define APP_EXTENSION_MACOS ""

class FileUtilsMacOS : public QObject
{
    Q_OBJECT
public:
    explicit FileUtilsMacOS(QObject *parent = nullptr);
    static QString GetRootDirByAppPath(QString appPath);
    static QString GetSubAppPathByRootAndSubName(QString rootDir, QString subAppName);
    static QString GetSubAppPathByAppAndSubName(QString appPath, QString subAppPath);

signals:

};

#endif // FILEUTILS_MACOS_H
#endif
