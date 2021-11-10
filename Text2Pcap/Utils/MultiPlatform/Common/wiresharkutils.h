#ifndef WIRESHARKUTILS_H
#define WIRESHARKUTILS_H

#include <QObject>
#include <QSettings>
#include <QMessageBox>
#include <QDateTime>
#include <QDir>
#include <QStandardPaths>

class WiresharkUtils : public QObject
{
    Q_OBJECT
public:
    explicit WiresharkUtils(QObject *parent = nullptr);
    static bool isWiresharkPathValid(QString displayCustomedWiresharkPath, QString &codeStr);
    static void writeWiresharkPathConfig(QString displayCustomedWiresharkPath);
    static void writePcapStoragePathConfig(QString pcapStoragePath);
    static void writePcapFormatConfig(QString pcapFormat);
    static QString getUsingDisplayWiresharkPath(QString customedDisplayWiresharkPath, QString detectedDisplayWiresharkPath);
    static QString geAppPathFromFile(QString appName);
    static QString getUsingDisplayWiresharkPath();
    static QString getAppPathByDisplayWiresharkPath(QString appName, QString wiresharkPath);
    static QString getPcapStoragePath();
    static QString getPcapFormatValue();
    static bool isAppNameSupport(QString appName);
    static QString getTex2PcapFormatString(QString str);
    static QString getTex2PcapFormatStringNew(QString str);
    static QString getParseFileName(QString rootPath, QDateTime curDateTime, QString prefix, QString suffix);
    static QString getHex2DumpTextFileName(QString prefix, QDateTime curDateTime);
    static QString getPcapFileName(QString rootPath, QDateTime curDateTime, QString prefix, QString suffix);
    static QString geAppPath(QString appName);
    static QString getSettingPath();
    static bool isValidWiresharkFileName(QString appName);

signals:

};

#endif // WIRESHARKUTILS_H
