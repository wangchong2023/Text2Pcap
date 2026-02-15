#ifndef TEXT2PCAPWIDGET_H
#define TEXT2PCAPWIDGET_H

#include "Service/text2pcap.h"
#include <QButtonGroup>
#include <QProcess>
#include <QString>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Text2PcapWidget;
}
QT_END_NAMESPACE

/**
 * @class Text2PcapWidget
 * @brief 应用主界面窗口，提供报文输入、配置选择和解析触发的 GUI 交互。
 *
 * 用户通过此界面输入十六进制报文、选择填充方式和输出格式，
 * 点击解析后委托 Text2Pcap 服务完成 pcap 文件生成。
 */
class Text2PcapWidget : public QWidget {
  Q_OBJECT

public:
  Text2PcapWidget(QWidget *parent = nullptr);

  ~Text2PcapWidget();

  /** @brief 获取 UI 指针，供外部初始化控件使用 */
  Ui::Text2PcapWidget *GetText2PcapWidgetUi();

  /** @brief 从系统配置中设置解析所需的路径参数 */
  static void setSysSetting2ParseParam(QString wiresharkPath,
                                       QString text2PcapPath,
                                       QString storageFilePath,
                                       QString saveFileSuffix);

private slots:
  void on_toolButton_BrowserWiresharkPath_clicked();

  void on_toolButton_BrowserCapStoragePath_clicked();

  void on_pushButton_SaveConfig_clicked();

  void on_pushButton_ParsePacket_clicked();

  void on_pushButton_CleanAllCapFiles_clicked();

  void on_pushButton_clearPacket_clicked();

  void on_pushButton_CopyPacket_clicked();

  void on_radioButton_No_Pad_clicked();

  void on_radioButton_Pad_LinkLayer_clicked();

  void on_radioButton_Pad_IPv4Layer_clicked();

  void on_radioButton_Pad_UDPLayer_clicked();

  void on_radioButton_Pad_TCPLayer_clicked();

  void on_radioButton_Packet_Content_Pad_Hex_Stream_clicked();

  void on_radioButton_Packet_Content_Pad_Hex_Dump_clicked();

  void on_radioButton_Output_Format_Pcap_clicked();

  void on_radioButton_Output_Format_PcapNG_clicked();

  void on_pushButton_CopyPacket2ClipBoard_clicked();

  void on_radioButton_Pad_IPv6Layer_clicked();

private:
  /** @brief 校验链路层类型输入是否合法 */
  bool isLinkTypeValid(QString linkTypeStr, uint32_t &linkType);
  /** @brief 校验协议号输入是否合法 */
  bool isProtoNumValid(QString ipProtoNumStr, uint32_t &ipProtoNum);
  /** @brief 校验源/目的端口号输入是否合法 */
  bool isPortNumsValid(QString srcPortNumStr, QString dstPortNumStr,
                       uint32_t &srcPortNum, uint32_t &dstPortNum);
  /** @brief 检查并裁剪报文内容 */
  QString checkAndTrimParsePacketContent(QString &packetContent);
  /** @brief 检查并获取填充信息 */
  bool checkAndGetPadInfo();

public:
  Ui::Text2PcapWidget *ui;

private:
  QButtonGroup *m_LinkTypeGroup;      ///< 链路层类型选择组
  QButtonGroup *m_PacketPadGroup;     ///< 报文填充方式选择组
  QButtonGroup *m_PacketContentGroup; ///< 报文内容格式选择组
  QButtonGroup *m_OutputFormatGroup;  ///< 输出文件格式选择组
  static parse_info m_parseConfig;    ///< 当前解析配置
};
#endif // TEXT2PCAPWIDGET_H
