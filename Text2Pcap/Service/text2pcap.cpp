#include "text2pcap.h"
#include "Common/common_header.h"

#include "Schedule/timerutils.h"
#include "Utils/System/processutils.h"
#include <QMessageBox>

Text2Pcap::Text2Pcap(QObject *parent) : QObject(parent) {}

void Text2Pcap::Initialize() {
  TIMER_REGISTER_S registerInfo = {};
  registerInfo.intervalMsec = TIMER_INTERVAL_MSEC_INFO_PROCESS;
  registerInfo.timer = new QTimer();
  registerInfo.repeat = true;
  registerInfo.timerType = TIMER_TYPE_INFO_PROCESS;
  registerInfo.pfCallBack = HandleTimeout;
  registerInfo.data = nullptr;

  TimerUtils::RegisterTimer(registerInfo);
}

parse_info Text2Pcap::m_parseInfo = Text2Pcap::initParseInfo();
bool Text2Pcap::m_isProcessText2PcapStarted = false;
bool Text2Pcap::m_isProcessWiresharkStarted = false;
uint32_t Text2Pcap::m_text2PcapRetryTimes = MAX_TEXT2PCAP_START_RETRY_TIMES;
uint32_t Text2Pcap::m_wiresharkRetryTimes = MAX_WIRESHARK_START_RETRY_TIMES;
uint32_t Text2Pcap::m_timerLoopTimes = MAX_TIMER_LOOP_TIMES;

parse_info Text2Pcap::initParseInfo() {
  parse_info parseInfo;

  parseInfo.linkType = LINK_TYPE_ETH;
  parseInfo.padType = PACKET_PAD_TYPE_NONE;
  parseInfo.hexDump = false;
  parseInfo.saveFileSuffix = FILE_EXTENTION_PCAP;
  parseInfo.dateTime = QDateTime::currentDateTime();

  return parseInfo;
}

void Text2Pcap::HandleTimeout(void *data) {
  Q_UNUSED(data);
  /* 1、避免定时器不终止，最长等待30s后终止处理 */
  DecreaseTimerLoopTimes();

  /* 2、正常或异常终止结束定时器，清理现场。 */
  if (checkComplete()) {
    ProcessAfterAllComplete();
    return;
  }

  /* 3、如果hex2Dump的文本文件不存在，则进行创建并写入（最长等待30s后终止）。 */
  if (!isHex2DumpTextFileExist()) {
    writeText2Pcap2File();
    return;
  }

  /* 4、如果解析后的文件不存在，则调用text2cap程序进行解析和文件保存。 */
  if (!isProcessText2PcapStarted()) {
    StartText2PcapProcess();
    DecreaseText2PcapRetryTimes();
    return;
  }

  /* 5、如果解析后的文件不存在，则继续等待（最长等待30s后终止）。 */
  if (!isPcapFileCreateComplete()) {
    return;
  }

  /* 6、如果Wireshark进程不存在，打开进程。 */
  StartWiresharkProcess();
  DecreaseWiresharkRetryTimes();
}

void Text2Pcap::ProcessAfterAllComplete() {
  /* 4、删除临时文本文件 */
  QString tmpTextFile = WiresharkUtils::getHex2DumpTextFileName(
      m_parseInfo.saveFileSuffix, m_parseInfo.dateTime);
  if (FileUtils::isFileExist(tmpTextFile)) {
    FileUtils::deleteFile(tmpTextFile);
  }

  /* 5、停止定时器 */
  TimerUtils::StopTimer(TIMER_TYPE_INFO_PROCESS);

  /* 初始化变量 */
  m_isProcessText2PcapStarted = false;
  m_isProcessWiresharkStarted = false;

  m_text2PcapRetryTimes = MAX_TEXT2PCAP_START_RETRY_TIMES;
  m_wiresharkRetryTimes = MAX_WIRESHARK_START_RETRY_TIMES;
  m_timerLoopTimes = MAX_TIMER_LOOP_TIMES;
}

bool Text2Pcap::isHex2DumpTextFileExist() {
  QString tmpFilePath = WiresharkUtils::getHex2DumpTextFileName(
      m_parseInfo.saveFileSuffix, m_parseInfo.dateTime);
  return FileUtils::isFileExist(tmpFilePath);
}

bool Text2Pcap::isHex2DumpTextFileWriteOver() {
  //    QString tmpFilePath =
  //    WiresharkUtils::getHex2DumpTextFileName(m_parseInfo.saveFileSuffix,
  //    m_parseInfo.dateTime); QFile tmpFile(tmpFilePath); quint64 fileSize =
  //    tmpFilePath.size(); quint64 text2PcapSize =
  //    m_parseInfo.text2PcapPacketContent.size();

  return true;
}

bool Text2Pcap::checkComplete() {
  if (!isParseInfoValid()) {
    QMessageBox::warning(nullptr, UI_RES_CONTROL_MESSAGEBOX_WARNING,
                         INFO_STRING_PARSE_PARAMS_INVALID);
    return true;
  }
  if (isTimerLoopTimesExceed()) {
    QMessageBox::warning(nullptr, UI_RES_CONTROL_MESSAGEBOX_WARNING,
                         INFO_STRING_PARSE_TEXT2PCAP_RETRY_EXCEED);
    return true;
  }
  if (isWiresharkRetryTimesExceed()) {
    QMessageBox::warning(nullptr, UI_RES_CONTROL_MESSAGEBOX_WARNING,
                         INFO_STRING_PARSE_WIRESHARK_RETRY_EXCEED);
    return true;
  }
  if (isProcessWiresharkStarted()) {
    return true;
  }

  return false;
}

bool Text2Pcap::isPcapFileCreateComplete() {
  QString pcapFilePath = WiresharkUtils::getPcapFileName(
      m_parseInfo.storageFilePath, m_parseInfo.dateTime,
      m_parseInfo.saveFileSuffix, m_parseInfo.saveFileSuffix);
  return FileUtils::isFileExist(pcapFilePath);
}

bool Text2Pcap::isProcessWiresharkStarted() {
  return m_isProcessWiresharkStarted;
}

void Text2Pcap::SetProcessWiresharkStarted() {
  m_isProcessWiresharkStarted = true;
}

bool Text2Pcap::isProcessText2PcapStarted() {
  return m_isProcessText2PcapStarted;
}

void Text2Pcap::SetProcessText2PcapStarted() {
  m_isProcessText2PcapStarted = true;
}

bool Text2Pcap::isWiresharkRetryTimesExceed() {
  return (m_wiresharkRetryTimes == 0);
}

bool Text2Pcap::isTimerLoopTimesExceed() { return (m_timerLoopTimes == 0); }

bool Text2Pcap::isParseInfoValid() {
  return (FileUtils::isFileExist(m_parseInfo.wiresharkPath) &&
          (FileUtils::isFileExist(m_parseInfo.text2PcapPath) &&
           (!m_parseInfo.text2PcapPacketContent.isEmpty())));
}

void Text2Pcap::DecreaseText2PcapRetryTimes() {
  if (m_text2PcapRetryTimes > 0) {
    m_text2PcapRetryTimes--;
  }
}

void Text2Pcap::DecreaseWiresharkRetryTimes() {
  if (m_wiresharkRetryTimes > 0) {
    m_wiresharkRetryTimes--;
  }
}

void Text2Pcap::DecreaseTimerLoopTimes() {
  if (m_timerLoopTimes > 0) {
    m_timerLoopTimes--;
  }
}

/*
 * https://www.wireshark.org/docs/man-pages/text2pcap.html
 *-e <l3pid>
 *-i <proto>
 *-n pcapng
 *-T <srcport>，<destport>
 *-u <srcport>，<destport>
 */
QString Text2Pcap::getText2PcapParamsByParseInfo() {
  QString strParam;
  switch (m_parseInfo.padType) {
  case PACKET_PAD_TYPE_NONE: {
    break;
  }
  /* -e <l3pid> */
  case PACKET_PAD_TYPE_LINK: {
    strParam = "-e " + QString::number(m_parseInfo.linkType, RADIX_HEX);
    break;
  }
  /* -i <proto> */
  case PACKET_PAD_TYPE_IPV4: {
    if (m_parseInfo.linkType == LINK_TYPE_ETH_IPV4) {
      strParam = TEXT2PCAP_OPT_ETH +
                 QString::number(m_parseInfo.linkType, RADIX_HEX) +
                 STRING_BLANK + TEXT2PCAP_OPT_IP_PRPOTO +
                 QString::number(m_parseInfo.ipv4ProtoNum);
    }
    break;
  }
  /* -i <proto> */
  case PACKET_PAD_TYPE_IPV6: {
    if (m_parseInfo.linkType == LINK_TYPE_ETH_IPV6) {
      strParam = TEXT2PCAP_OPT_ETH +
                 QString::number(m_parseInfo.linkType, RADIX_HEX) +
                 STRING_BLANK + TEXT2PCAP_OPT_IP_PRPOTO +
                 QString::number(m_parseInfo.ipv6ProtoNum);
    }
    break;
  }
  /* -T <srcport>，<destport> */
  case PACKET_PAD_TYPE_TCP: {
    strParam = TEXT2PCAP_OPT_TCP_PORT +
               QString::number(m_parseInfo.srcPortNum) + STRING_COMMA +
               QString::number(m_parseInfo.dstPortNum);
    break;
  }
  /* -u <srcport>，<destport> */
  case PACKET_PAD_TYPE_UDP: {
    strParam = TEXT2PCAP_OPT_UDP_PORT +
               QString::number(m_parseInfo.srcPortNum) + STRING_COMMA +
               QString::number(m_parseInfo.dstPortNum);
    break;
  }
  default: {
    break;
  }
  }

  return strParam;
}

/*
 * https://www.wireshark.org/docs/man-pages/text2pcap.html
 * text2pcap [ -a ] [ -d ] [ -D ] [ -e <l3pid> ] [ -h ] [ -i <proto> ] [ -l
 *<typenum> ] [ -n ] [ -N <intf-name> ] [ -m <max-packet> ] [ -o hex|oct|dec ] [
 *-q ] [ -s <srcport>,<destport>,<tag> ] [ -S <srcport>,<destport>,<ppi> ] [ -t
 *<timefmt> ] [ -T <srcport>,<destport> ] [ -u <srcport>,<destport> ] [ -v ] [
 *-4 <srcip>,<destip> ] [ -6 <srcip>,<destip> ] <infile>|- <outfile>|-
 *
 *Example:
 *./text2pcap /Users/constantine/Downloads/hex2dump.txt
 * /Users/constantine/Downloads/test.pcap
 */
bool Text2Pcap::StartText2PcapProcess() {
  QString text2capPath = m_parseInfo.text2PcapPath;

  QString srcHex2DumpFilePath = WiresharkUtils::getHex2DumpTextFileName(
      m_parseInfo.saveFileSuffix, m_parseInfo.dateTime);
  QString dstSaveFilePath = WiresharkUtils::getPcapFileName(
      m_parseInfo.storageFilePath, m_parseInfo.dateTime,
      m_parseInfo.saveFileSuffix, m_parseInfo.saveFileSuffix);
  QStringList argsListText2Pcap;
  QString text2PcapParams = getText2PcapParamsByParseInfo();
  if (text2PcapParams.isEmpty()) {
    argsListText2Pcap << srcHex2DumpFilePath << dstSaveFilePath;
  } else {
    argsListText2Pcap << text2PcapParams << srcHex2DumpFilePath
                      << dstSaveFilePath;
  }

  (void)ProcessUtils::StartDetachedProcess(text2capPath, argsListText2Pcap,
                                           TIME_WAIT_READY_READ_MSEC);
  SetProcessText2PcapStarted();

  return true;
}

bool Text2Pcap::StartWiresharkProcess() {
  QString wiresharkDisplayPath = m_parseInfo.wiresharkPath;

  QString pCapFilePath = WiresharkUtils::getPcapFileName(
      m_parseInfo.storageFilePath, m_parseInfo.dateTime,
      m_parseInfo.saveFileSuffix, m_parseInfo.saveFileSuffix);
  QStringList argsListWireshark;
  argsListWireshark << pCapFilePath;

  (void)ProcessUtils::StartDetachedProcess(
      wiresharkDisplayPath, argsListWireshark, TIME_WAIT_READY_READ_MSEC);
  SetProcessWiresharkStarted();

  return true;
}

void Text2Pcap::writeText2Pcap2File() {
  QString tmpFilePath = WiresharkUtils::getHex2DumpTextFileName(
      m_parseInfo.saveFileSuffix, m_parseInfo.dateTime);
  FileUtils::writeText2File(tmpFilePath, m_parseInfo.text2PcapPacketContent);
}

void Text2Pcap::StartProcess(parse_info &parseInfo) {
  m_parseInfo.linkType = parseInfo.linkType;
  m_parseInfo.padType = parseInfo.padType;
  m_parseInfo.ipv4ProtoNum = parseInfo.ipv4ProtoNum;
  m_parseInfo.ipv6ProtoNum = parseInfo.ipv6ProtoNum;
  m_parseInfo.srcPortNum = parseInfo.srcPortNum;
  m_parseInfo.dstPortNum = parseInfo.dstPortNum;
  m_parseInfo.hexDump = parseInfo.hexDump;
  m_parseInfo.dateTime = parseInfo.dateTime;
  m_parseInfo.text2PcapPacketContent = parseInfo.text2PcapPacketContent;

  m_parseInfo.wiresharkPath = parseInfo.wiresharkPath;
  m_parseInfo.text2PcapPath = parseInfo.text2PcapPath;

  m_parseInfo.storageFilePath = parseInfo.storageFilePath;
  m_parseInfo.saveFileSuffix = parseInfo.saveFileSuffix;

  /* 启动定时器异步处理 */
  TimerUtils::StartTimer(TIMER_TYPE_INFO_PROCESS);
}
