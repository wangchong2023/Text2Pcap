#ifndef TEXT2PCAP_H
#define TEXT2PCAP_H

#include <QObject>
#include <QString>
#include <QProcess>
#include <QDateTime>
#include "Common/common_def.h"
#include "Schedule/timerutils.h"

typedef struct parse_info {
    uint32_t linkType;              //待解析的链路层类型
    uint32_t padType;               //待填充的类型
    uint32_t ipv4ProtoNum;          //IPv4协议号
    uint32_t ipv6ProtoNum;          //IPv6协议号
    uint32_t srcPortNum;            //源端口
    uint32_t dstPortNum;            //目的端口
    bool hexDump;                   //报文内容是否为Hex Dump格式
    QDateTime dateTime;             //处理报文的时间
    QString text2PcapPacketContent; //text2Pcap格式文件内容
    QString wiresharkPath;          //Wireshark文件路径
    QString text2PcapPath;          //Text2Pcap文件路径
    QString storageFilePath;        //存储文件路径
    QString saveFileSuffix;         //保存文件的后缀
} parse_info;

class Text2Pcap : public QObject
{
    Q_OBJECT
private:
    explicit Text2Pcap(QObject *parent = nullptr);

    static void HandleTimeout(void* data) ;
    static void ProcessAfterAllComplete();
    static bool isHex2DumpTextFileExist();
    static bool isHex2DumpTextFileWriteOver();
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
    static QString getText2PcapParamsByParseInfo();
    static bool StartText2PcapProcess();
    static bool StartWiresharkProcess();
    static void writeText2Pcap2File();


public:
    static void Initialize();
    static parse_info initParseInfo();
    static void StartProcess(parse_info &parseInfo);

signals:
private:
    static parse_info m_parseInfo;
    static uint32_t m_text2PcapRetryTimes;
    static uint32_t m_wiresharkRetryTimes;
    static uint32_t m_timerLoopTimes;
    static bool m_isProcessText2PcapStarted;
    static bool m_isProcessWiresharkStarted;
};

#endif // TEXT2PCAP_H
