#include "wiresharkutils_win.h"
#include "Common/common_def.h"

#ifdef Q_OS_WIN
WiresharkUtilsWin::WiresharkUtilsWin(QObject *parent) : QObject(parent)
{
    //filePathMap.insert(APP_NAME_WIRESHARK_WIN, APP_NAME_WIRESHARK_PATH_WIN);
}

QString WiresharkUtilsWin::geAppPath(QString appName) {
    if (appName.isEmpty()) {
        qWarning("AppName is empty.");
        return nullptr;
    }

    if (appName.compare(APP_NAME_WIRESHARK_WIN) != 0) {
        return "";
    }

    QSettings reg(APP_NAME_WIRESHARK_PATH_WIN, QSettings::NativeFormat);
    QString path= reg.value(APP_NAME_WIRESHARK_REG_ITEM).toString();
    return path;
}

bool WiresharkUtilsWin::isValidWiresharkFileName(QString appName) {
    return ((appName == APP_NAME_WIRESHARK) || (appName == QString(APP_NAME_WIRESHARK) + ".exe"));
}
#endif //Q_OS_WIN
