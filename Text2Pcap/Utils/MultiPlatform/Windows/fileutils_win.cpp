#include "fileutils_win.h"
#include "Common/common_header.h"

#ifdef Q_OS_WIN
FileUtilsWin::FileUtilsWin(QObject *parent) : QObject(parent)
{

}

QString FileUtilsWin::GetRootDirByAppPath(QString appPath) {
    if (appPath.isEmpty()) {
        qWarning("AppPath is empty.");
        return nullptr;
    }

    return QFileInfo(appPath).canonicalPath();
}

QString FileUtilsWin::GetSubAppPathByRootAndSubName(QString rootDir, QString subAppName) {
    if ((rootDir.isEmpty()) || (subAppName.isEmpty())) {
        qWarning("RootDir or subAppName is empty.");
        return nullptr;
    }

    QString appPath = rootDir.append(QDir::separator()).append(subAppName).append(APP_EXTENSION_WIN);
    QString appCanonicalPath = QFileInfo(appPath).canonicalFilePath();

    return appCanonicalPath;
}

QString FileUtilsWin::GetSubAppPathByAppAndSubName(QString appPath, QString subAppName) {
   if ((appPath.isEmpty()) || (subAppName.isEmpty())) {
       qWarning("AppPath or subAppName is empty.");
       return nullptr;
   }

   QString rootDir = GetRootDirByAppPath(appPath);
   if (rootDir.isEmpty()) {
       qWarning("RootDir is empty.");
       return nullptr;
   }

   return GetSubAppPathByRootAndSubName(rootDir, subAppName);
}

#endif //Q_OS_WIN
