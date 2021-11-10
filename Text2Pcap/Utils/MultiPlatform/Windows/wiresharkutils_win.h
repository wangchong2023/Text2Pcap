#ifndef WIRESHARKUTILS_WIN_H
#define WIRESHARKUTILS_WIN_H

#include <QtGlobal>

#ifdef Q_OS_WIN

#include <QObject>
#include <QString>
#include <QMap>
#include <QSettings>
#include <QDebug>
#include <QDir>

#define APP_NAME_WIRESHARK_WIN        "Wireshark"
#define APP_NAME_WIRESHARK_PATH_WIN   "\\HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\Wireshark.exe"
#define APP_NAME_WIRESHARK_REG_ITEM   "."

class WiresharkUtilsWin : public QObject
{
    Q_OBJECT
public:
    explicit WiresharkUtilsWin(QObject *parent = nullptr);
    static QString geAppPath(QString appName);
    static bool isValidWiresharkFileName(QString appName);
signals:

private:
    static QMap<QString, QString> filePathMap;
};

#endif // WIRESHARKUTILS_WIN_H
#endif
