#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <QObject>
#include <QFile>
#include <QTextStream>

#include "Utils/MultiPlatform/MacOS/fileutils_macos.h"
#include "Utils/MultiPlatform/Windows/fileutils_win.h"

class FileUtils : public QObject
{
    Q_OBJECT
public:
    explicit FileUtils(QObject *parent = nullptr);
    static QString GetRootDirByAppPath(QString appPath);
    static QString GetSubAppPathByRootAndSubName(QString rootDir, QString subAppName);
    static QString GetSubAppPathByAppAndSubName(QString appPath, QString subAppPath);
    static bool isFile(QString filePath);
    static bool isDir(QString dirPath);
    static bool isFileExist(QString appPath);
    static bool isDirExist(QString dirPath);
    static QString getAppNameByPath(QString appPath);
    static QString getAppCanonicalByPath(QString appPath);
    static QString getAppSuffixByPath(QString appPath);
    static QString getAppAbsoluteByPath(QString appPath);
    static void writeText2File(QString textPath, QString text);
    static void deleteFile(QString filePath);
    static uint32_t deleteFilesBySuffix(QString dirPath, QString suffix);
    static void deleteDirAndSubFiles(QString dirPath);

signals:

};

#endif // FILEUTILS_H
