#ifndef WIRESHARKUTILS_MACOS_H
#define WIRESHARKUTILS_MACOS_H

#include <QtGlobal>

#ifdef Q_OS_MACOS

#include <QMap>
#include <QObject>
#include <QString>

#define APP_NAME_WIRESHARK_MACOS "Wireshark"
#define APP_NAME_WIRESHARK_PATH_MACOS "/Applications/Wireshark.app"

class WiresharkUtilsMacOS : public QObject {
  Q_OBJECT
public:
  explicit WiresharkUtilsMacOS(QObject *parent = nullptr);
  static QString geAppPath(QString appName);
  static bool isValidWiresharkFileName(QString appName);
signals:

private:
  static QMap<QString, QString> filePathMap;
};

#endif // WIRESHARKUTILS_MACOS_H
#endif
