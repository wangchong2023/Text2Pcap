#ifndef FILEUTILS_WIN_H
#define FILEUTILS_WIN_H

#include <QtGlobal>

#ifdef Q_OS_WIN

#include <QObject>

#define APP_EXTENSION_WIN ".exe"

class FileUtilsWin : public QObject
{
    Q_OBJECT
public:
    explicit FileUtilsWin(QObject *parent = nullptr);
    static QString GetRootDirByAppPath(QString appPath);
    static QString GetSubAppPathByRootAndSubName(QString rootDir, QString subAppName);
    static QString GetSubAppPathByAppAndSubName(QString appPath, QString subAppPath);
signals:

};

#endif // FILEUTILS_WIN_H

#endif
