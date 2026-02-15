#include "wiresharkutils_macos.h"
#include "Common/common_def.h"

#ifdef Q_OS_MACOS
WiresharkUtilsMacOS::WiresharkUtilsMacOS(QObject *parent) : QObject(parent) {
  // filePathMap.insert(APP_NAME_WIRESHARK_MACOS,
  // APP_NAME_WIRESHARK_PATH_MACOS);
}

QString WiresharkUtilsMacOS::geAppPath(QString appName) {
  if (appName.isEmpty()) {
    qWarning("AppName is empty.");
    return nullptr;
  }
  if (appName.compare(APP_NAME_WIRESHARK_MACOS) != 0) {
    return "";
  }

  return APP_NAME_WIRESHARK_PATH_MACOS;
}

bool WiresharkUtilsMacOS::isValidWiresharkFileName(QString appName) {
  return ((appName == APP_NAME_WIRESHARK) ||
          (appName == QString(APP_NAME_WIRESHARK) + ".app"));
}
#endif // Q_OS_MACOS
