#include "fileutils_macos.h"

#ifdef Q_OS_MACOS

FileUtilsMacOS::FileUtilsMacOS(QObject *parent) : QObject(parent) {}

/* /Applications/Wireshark.app */
/* /Applications/Wireshark.app/Contents/MacOS/text2pcap */
QString FileUtilsMacOS::GetRootDirByAppPath(QString appPath) {
  if (appPath.isEmpty()) {
    qWarning("AppPath is empty.");
    return nullptr;
  }

  return appPath.append(FILE_UTILS_PREFIX_MACOS);
}

QString FileUtilsMacOS::GetSubAppPathByRootAndSubName(QString rootDir,
                                                      QString subAppName) {
  if ((rootDir.isEmpty()) || (subAppName.isEmpty())) {
    qWarning("RootDir or subAppName is empty.");
    return nullptr;
  }

  return rootDir.append(subAppName).append(APP_EXTENSION_MACOS);
}

QString FileUtilsMacOS::GetSubAppPathByAppAndSubName(QString appPath,
                                                     QString subAppName) {
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

#endif // Q_OS_MACOS
