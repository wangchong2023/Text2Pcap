#ifndef TEXT2PCAP_H
#define TEXT2PCAP_H

#include "Common/common_def.h"
#include "Schedule/timerutils.h"
#include <QDateTime>
#include <QObject>
#include <QProcess>
#include <QString>

/** @brief 报文解析参数结构体 */
typedef struct parse_info {
  uint32_t linkType;              ///< 待解析的链路层类型
  uint32_t padType;               ///< 待填充的类型
  uint32_t ipv4ProtoNum;          ///< IPv4协议号
  uint32_t ipv6ProtoNum;          ///< IPv6协议号
  uint32_t srcPortNum;            ///< 源端口
  uint32_t dstPortNum;            ///< 目的端口
  bool hexDump;                   ///< 报文内容是否为Hex Dump格式
  QDateTime dateTime;             ///< 处理报文的时间
  QString text2PcapPacketContent; ///< text2Pcap格式文件内容
  QString wiresharkPath;          ///< Wireshark文件路径
  QString text2PcapPath;          ///< Text2Pcap文件路径
  QString storageFilePath;        ///< 存储文件路径
  QString saveFileSuffix;         ///< 保存文件的后缀
} parse_info;

/**
 * @class Text2Pcap
 * @brief 报文解析核心服务类。
 *
 * 负责将用户输入的十六进制报文文本通过 Wireshark 的 text2pcap 工具
 * 转换为 pcap/pcapng 文件，并自动启动 Wireshark 打开结果。
 * 使用定时器轮询机制等待 text2pcap 和 Wireshark 进程完成。
 */
class Text2Pcap : public QObject {
  Q_OBJECT
private:
  explicit Text2Pcap(QObject *parent = nullptr);

  /** @brief 定时器超时回调，驱动解析流程的状态机 */
  static void HandleTimeout(void *data);
  /** @brief 所有步骤完成后的清理处理 */
  static void ProcessAfterAllComplete();
  static bool isHex2DumpTextFileExist();
  static bool isHex2DumpTextFileWriteOver();
  /** @brief 检查解析流程是否完成（含异常退出判断） */
  static bool checkComplete();
  static bool isPcapFileCreateComplete();
  static void SetProcessText2PcapStarted();
  static bool isProcessWiresharkStarted();
  static void SetProcessWiresharkStarted();
  static bool isProcessText2PcapStarted();
  static bool isWiresharkRetryTimesExceed();
  static bool isTimerLoopTimesExceed();
  static bool isParseInfoValid();
  static void DecreaseText2PcapRetryTimes();
  static void DecreaseWiresharkRetryTimes();
  static void DecreaseTimerLoopTimes();
  /** @brief 根据 parseInfo 组装 text2pcap 命令行参数 */
  static QString getText2PcapParamsByParseInfo();
  static bool StartText2PcapProcess();
  static bool StartWiresharkProcess();
  /** @brief 将格式化后的报文写入临时文件 */
  static void writeText2Pcap2File();

public:
  /** @brief 初始化解析服务（注册定时器等） */
  static void Initialize();
  /** @brief 创建默认解析参数 */
  static parse_info initParseInfo();
  /** @brief 启动解析流程 */
  static void StartProcess(parse_info &parseInfo);

signals:
private:
  static parse_info m_parseInfo;           ///< 当前解析参数
  static uint32_t m_text2PcapRetryTimes;   ///< text2pcap 重试剩余次数
  static uint32_t m_wiresharkRetryTimes;   ///< Wireshark 重试剩余次数
  static uint32_t m_timerLoopTimes;        ///< 定时器轮询剩余次数
  static bool m_isProcessText2PcapStarted; ///< text2pcap 进程是否已启动
  static bool m_isProcessWiresharkStarted; ///< Wireshark 进程是否已启动
};

#endif // TEXT2PCAP_H
