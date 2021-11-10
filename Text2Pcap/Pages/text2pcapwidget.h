#ifndef TEXT2PCAPWIDGET_H
#define TEXT2PCAPWIDGET_H

#include <QWidget>
#include <QButtonGroup>
#include <QString>
#include <QProcess>
#include "Service/text2pcap.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Text2PcapWidget; }
QT_END_NAMESPACE

class Text2PcapWidget : public QWidget
{
    Q_OBJECT

public:
    Text2PcapWidget(QWidget *parent = nullptr);

    ~Text2PcapWidget();

    Ui::Text2PcapWidget* GetText2PcapWidgetUi();

    static void setSysSetting2ParseParam(QString wiresharkPath, QString text2PcapPath, QString storageFilePath, QString saveFileSuffix);

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
    bool isLinkTypeValid(QString linkTypeStr, uint32_t &linkType);

    bool isProtoNumValid(QString ipProtoNumStr, uint32_t &ipProtoNum);

    bool isPortNumsValid(QString srcPortNumStr, QString dstPortNumStr, uint32_t &srcPortNum, uint32_t &dstPortNum);

    QString checkAndTrimParsePacketContent(QString& packetContent);

    bool checkAndGetPadInfo();

public:
    Ui::Text2PcapWidget *ui;
private:
    QButtonGroup *m_LinkTypeGroup;
    QButtonGroup *m_PacketPadGroup;
    QButtonGroup *m_PacketContentGroup;
    QButtonGroup *m_OutputFormatGroup;
    static parse_info m_parseConfig;
};
#endif // TEXT2PCAPWIDGET_H
