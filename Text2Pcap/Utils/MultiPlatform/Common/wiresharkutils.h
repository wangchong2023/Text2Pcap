#ifndef WIRESHARKUTILS_H
#define WIRESHARKUTILS_H

#include <QDateTime>
#include <QDir>
#include <QMessageBox>
#include <QObject>
#include <QSettings>
#include <QStandardPaths>

/**
 * @class WiresharkUtils
 * @brief Wireshark / text2pcap 交互工具类。
 *
 * 提供 Wireshark 路径检测、配置读写、报文格式转换和文件名生成等功能。
 * 配置使用 QSettings（INI 格式）持久化。
 */
class WiresharkUtils : public QObject {
  Q_OBJECT
public:
  explicit WiresharkUtils(QObject *parent = nullptr);

  /** @brief 校验 Wireshark 路径是否有效 */
  static bool isWiresharkPathValid(QString displayCustomedWiresharkPath,
                                   QString &codeStr);
  /** @brief 保存自定义 Wireshark 路径到配置文件 */
  static void writeWiresharkPathConfig(QString displayCustomedWiresharkPath);
  /** @brief 保存 pcap 文件存储路径到配置文件 */
  static void writePcapStoragePathConfig(QString pcapStoragePath);
  /** @brief 保存 pcap 输出格式到配置文件 */
  static void writePcapFormatConfig(QString pcapFormat);
  /** @brief 获取优先使用的 Wireshark 显示路径（自定义 > 自动检测） */
  static QString
  getUsingDisplayWiresharkPath(QString customedDisplayWiresharkPath,
                               QString detectedDisplayWiresharkPath);
  /** @brief 从配置文件读取应用路径 */
  static QString geAppPathFromFile(QString appName);
  /** @brief 获取当前生效的 Wireshark 显示路径 */
  static QString getUsingDisplayWiresharkPath();
  /** @brief 根据应用名和 Wireshark 路径推导可执行文件路径 */
  static QString getAppPathByDisplayWiresharkPath(QString appName,
                                                  QString wiresharkPath);
  /** @brief 从配置文件读取 pcap 存储路径 */
  static QString getPcapStoragePath();
  /** @brief 从配置文件读取 pcap 输出格式 */
  static QString getPcapFormatValue();
  /** @brief 判断应用名是否受支持 */
  static bool isAppNameSupport(QString appName);
  /** @brief 将原始报文文本转换为 text2pcap 格式 */
  static QString getTex2PcapFormatString(QString str);
  /** @brief 将原始报文文本转换为 text2pcap 格式（新版算法） */
  static QString getTex2PcapFormatStringNew(QString str);
  /** @brief 生成解析文件名 */
  static QString getParseFileName(QString rootPath, QDateTime curDateTime,
                                  QString prefix, QString suffix);
  /** @brief 生成 hex dump 临时文件名 */
  static QString getHex2DumpTextFileName(QString prefix, QDateTime curDateTime);
  /** @brief 生成 pcap 输出文件名 */
  static QString getPcapFileName(QString rootPath, QDateTime curDateTime,
                                 QString prefix, QString suffix);
  /** @brief 自动检测系统中的应用路径 */
  static QString geAppPath(QString appName);
  /** @brief 获取配置文件路径 */
  static QString getSettingPath();
  /** @brief 验证文件名是否为合法的 Wireshark 可执行文件名 */
  static bool isValidWiresharkFileName(QString appName);

signals:
};

#endif // WIRESHARKUTILS_H
