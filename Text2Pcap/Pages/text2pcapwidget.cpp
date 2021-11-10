#include "Common/sys_header.h"
#include "Common/ui_header.h"
#include "Common/infostring.h"
#include "Utils/MultiPlatform/Common/fileutils.h"
#include "Utils/MultiPlatform/Common/wiresharkutils.h"
#include "Utils/Tools/buildutils.h"
#include "Utils/Tools/stringutils.h"
#include "Service/text2pcap.h"

Text2PcapWidget::Text2PcapWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Text2PcapWidget)
{
    ui->setupUi(this);

    m_LinkTypeGroup = new QButtonGroup();
    m_LinkTypeGroup->addButton(ui->radioButton_Ethernet);
    ui->radioButton_Ethernet->setChecked(true);

    m_PacketPadGroup = new QButtonGroup();
    m_PacketPadGroup->addButton(ui->radioButton_No_Pad);
    m_PacketPadGroup->addButton(ui->radioButton_Pad_LinkLayer);
    m_PacketPadGroup->addButton(ui->radioButton_Pad_IPv4Layer);
    m_PacketPadGroup->addButton(ui->radioButton_Pad_UDPLayer);
    m_PacketPadGroup->addButton(ui->radioButton_Pad_TCPLayer);
    ui->radioButton_No_Pad->setChecked(true);

    m_PacketContentGroup = new QButtonGroup();
    m_PacketContentGroup->addButton(ui->radioButton_Packet_Content_Pad_Hex_Stream);
    m_PacketContentGroup->addButton(ui->radioButton_Packet_Content_Pad_Hex_Dump);
    ui->radioButton_Packet_Content_Pad_Hex_Stream->setChecked(true);

    m_OutputFormatGroup = new QButtonGroup();
    m_OutputFormatGroup->addButton(ui->radioButton_Output_Format_Pcap);
    m_OutputFormatGroup->addButton(ui->radioButton_Output_Format_PcapNG);
    ui->radioButton_Output_Format_Pcap->setChecked(true);
}

Text2PcapWidget::~Text2PcapWidget()
{
    delete m_LinkTypeGroup;
    delete m_PacketPadGroup;
    delete m_PacketContentGroup;
    delete m_OutputFormatGroup;

    delete ui;
}

parse_info Text2PcapWidget::m_parseConfig = Text2Pcap::initParseInfo();

Ui::Text2PcapWidget*Text2PcapWidget::GetText2PcapWidgetUi() {
    return ui;
}

void Text2PcapWidget::setSysSetting2ParseParam(QString wiresharkPath, QString text2PcapPath, QString storageFilePath, QString saveFileSuffix) {
    m_parseConfig.wiresharkPath = wiresharkPath;
    m_parseConfig.text2PcapPath = text2PcapPath;
    m_parseConfig.storageFilePath = storageFilePath;
    m_parseConfig.saveFileSuffix = saveFileSuffix;
}

void Text2PcapWidget::on_toolButton_BrowserWiresharkPath_clicked()
{
    QString wireshakSelectedPath = QFileDialog::getOpenFileName(this, UI_RES_CONTROL_TEXT2WIDGET_WS_DIAG_TITLE, STRING_SLASH);
    if (wireshakSelectedPath.isEmpty()) {
        return;
    }

    ui->lineEdit_WiresharkPath->setText(wireshakSelectedPath);
}

void Text2PcapWidget::on_toolButton_BrowserCapStoragePath_clicked()
{
    QString pcapStoragePath = QFileDialog::getExistingDirectory(this, UI_RES_CONTROL_TEXT2WIDGET_PCAP_DIAG_TITLE, STRING_SLASH);
    pcapStoragePath = QDir::toNativeSeparators(pcapStoragePath);
    if (pcapStoragePath.isEmpty()) {
        return;
    }

    ui->lineEdit_CapStoragePath->setText(pcapStoragePath);
}

void Text2PcapWidget::on_pushButton_SaveConfig_clicked()
{
    QString customedWiresharkPath = ui->lineEdit_WiresharkPath->text();
    QString strCode;
    if (!WiresharkUtils::isWiresharkPathValid(customedWiresharkPath, strCode)) {
        QMessageBox::warning(nullptr, UI_RES_CONTROL_MESSAGEBOX_WARNING, strCode);
        return;
    }

    QString storageFilePath = ui->lineEdit_CapStoragePath->text();
    if (!FileUtils::isDirExist(storageFilePath)) {
        QMessageBox::warning(nullptr, UI_RES_CONTROL_MESSAGEBOX_WARNING, INFO_STRING_PCAP_SAVE_PATH_INVALID);
        return;
    }

    m_parseConfig.storageFilePath = storageFilePath;
    m_parseConfig.wiresharkPath = WiresharkUtils::getAppPathByDisplayWiresharkPath(APP_NAME_WIRESHARK, customedWiresharkPath);
    m_parseConfig.text2PcapPath = WiresharkUtils::getAppPathByDisplayWiresharkPath(APP_NAME_TEXT2CAP, customedWiresharkPath);

    /* 保存到配置数据到文件 */
    WiresharkUtils::writeWiresharkPathConfig(customedWiresharkPath);
    WiresharkUtils::writePcapStoragePathConfig(storageFilePath);
    WiresharkUtils::writePcapFormatConfig(m_parseConfig.saveFileSuffix);
}

bool Text2PcapWidget::isLinkTypeValid(QString linkTypeStr, uint32_t &linkType)
{
    if (linkTypeStr.isEmpty()) {
        QMessageBox::warning(this, UI_RES_CONTROL_MESSAGEBOX_WARNING, INFO_STRING_INPUT_INVALID_EMPTY);
        return false;
    }

    if (!StringUtils::isHexString(linkTypeStr)) {
        QMessageBox::warning(this, UI_RES_CONTROL_MESSAGEBOX_WARNING, INFO_STRING_INPUT_INVALID_NOT_HEX_DIGITAL);
        return false;
    }

    linkType = linkTypeStr.toInt(nullptr, RADIX_HEX);
    if (linkType > LINK_TYPE_MAX) {
        QMessageBox::warning(this, UI_RES_CONTROL_MESSAGEBOX_WARNING, INFO_STRING_LINK_TYPE_EXCEED_MAX);
        return false;
    }

    return true;
}

bool Text2PcapWidget::isProtoNumValid(QString ipProtoNumStr, uint32_t &ipProtoNum)
{
    if (ipProtoNumStr.isEmpty()) {
        QMessageBox::warning(this, UI_RES_CONTROL_MESSAGEBOX_WARNING, INFO_STRING_INPUT_INVALID_EMPTY);
        return false;
    }

    if (!StringUtils::isDigitalString(ipProtoNumStr)) {
        QMessageBox::warning(this, UI_RES_CONTROL_MESSAGEBOX_WARNING, INFO_STRING_INPUT_INVALID_NOT_DIGITAL);
        return false;
    }

    ipProtoNum = ipProtoNumStr.toUInt();
    if (ipProtoNum > IP_PROTO_NUM_MAX) {
        QMessageBox::warning(this, UI_RES_CONTROL_MESSAGEBOX_WARNING, INFO_STRING_IP_PROTO_NUM_EXCEED_MAX);
        return false;
    }

    return true;
}

bool Text2PcapWidget::isPortNumsValid(QString srcPortNumStr, QString dstPortNumStr, uint32_t &srcPortNum, uint32_t &dstPortNum)
{
    if (srcPortNumStr.isEmpty()) {
        QMessageBox::warning(this, UI_RES_CONTROL_MESSAGEBOX_WARNING, INFO_STRING_INPUT_INVALID_EMPTY);
        return false;
    }
    if (!StringUtils::isDigitalString(srcPortNumStr)) {
        QMessageBox::warning(this, UI_RES_CONTROL_MESSAGEBOX_WARNING, INFO_STRING_INPUT_INVALID_NOT_DIGITAL);
        return false;
    }
    if (dstPortNumStr.isEmpty()) {
        QMessageBox::warning(this, UI_RES_CONTROL_MESSAGEBOX_WARNING, INFO_STRING_INPUT_INVALID_EMPTY);
        return false;
    }
    if (!StringUtils::isDigitalString(dstPortNumStr)) {
        QMessageBox::warning(this, UI_RES_CONTROL_MESSAGEBOX_WARNING, INFO_STRING_INPUT_INVALID_NOT_DIGITAL);
        return false;
    }

    srcPortNum = srcPortNumStr.toUInt();
    if (srcPortNum > PORT_NUM_MAX) {
        QMessageBox::warning(this, UI_RES_CONTROL_MESSAGEBOX_WARNING, INFO_STRING_SRC_PORT_NUM_EXCEED_MAX);
        return false;
    }
    dstPortNum = dstPortNumStr.toUInt();
    if (dstPortNum > PORT_NUM_MAX) {
        QMessageBox::warning(this, UI_RES_CONTROL_MESSAGEBOX_WARNING, INFO_STRING_DST_PORT_NUM_EXCEED_MAX);
        return false;
    }

    return true;
}

bool Text2PcapWidget::checkAndGetPadInfo()
{
    uint32_t linkType = LINK_TYPE_MIN;
    uint32_t ipv4ProtoNum = IP_PROTO_NUM_MIN;
    uint32_t ipv6ProtoNum = IP_PROTO_NUM_MIN;
    uint32_t srcPortNum = PORT_NUM_MIN;
    uint32_t dstPortNum = PORT_NUM_MIN;

    if (ui->radioButton_No_Pad->isChecked()) {
        //Do nothing
    } else if (ui->radioButton_Pad_LinkLayer->isChecked()) {
        if (!(isLinkTypeValid(ui->lineEdit_Link_Type_Value->text(), linkType))) {
            return false;
        }
    } else if (ui->radioButton_Pad_IPv4Layer->isChecked()) {
        if (!(isProtoNumValid(ui->lineEdit_IPv4_Proto_Num_Value->text(), ipv4ProtoNum))) {
            return false;
        }
        linkType = LINK_TYPE_ETH_IPV4;
    } else if (ui->radioButton_Pad_TCPLayer->isChecked()) {
        if (!isPortNumsValid(ui->lineEdit_TCP_Src_Port_Value->text(), ui->lineEdit_TCP_Dst_Port_Value->text(), srcPortNum, dstPortNum)) {
            return false;
        }
    } else if (ui->radioButton_Pad_UDPLayer->isChecked()) {
        if (!isPortNumsValid(ui->lineEdit_UDP_Src_Port_Value->text(), ui->lineEdit_UDP_Dst_Port_Value->text(), srcPortNum, dstPortNum)) {
            return false;
        }
    } else {
        QMessageBox::warning(this, UI_RES_CONTROL_MESSAGEBOX_WARNING, INFO_STRING_INPUT_INVALID);
        return false;
    }

    m_parseConfig.linkType = linkType;
    m_parseConfig.ipv4ProtoNum = ipv4ProtoNum;
    m_parseConfig.ipv6ProtoNum = ipv6ProtoNum;
    m_parseConfig.srcPortNum = srcPortNum;
    m_parseConfig.dstPortNum = dstPortNum;

    return true;
}

QString Text2PcapWidget::checkAndTrimParsePacketContent(QString& packetContent)
{
    if (packetContent.isEmpty()) {
        QMessageBox::warning(this, UI_RES_CONTROL_MESSAGEBOX_WARNING, INFO_STRING_PACKET_CONTENT_EMPTY);
        return STRING_EMPTY;
    }

    StringUtils::TrimBlankString(packetContent);
    if (packetContent.size() > PACKET_CONTENT_MAX_SIZE) {
        QMessageBox::warning(this, UI_RES_CONTROL_MESSAGEBOX_WARNING, INFO_STRING_PACKET_LENGTH_EXCEED);
        return STRING_EMPTY;
    }

    if (!StringUtils::isHexString(packetContent)) {
        QMessageBox::warning(this, UI_RES_CONTROL_MESSAGEBOX_WARNING, INFO_STRING_PACKET_CONTENT_INVALID);
        return STRING_EMPTY;
    }

    if (packetContent.isEmpty()) {
        QMessageBox::warning(this, UI_RES_CONTROL_MESSAGEBOX_WARNING, INFO_STRING_PACKET_CONTENT_TRIM_EMPTY);
        return STRING_EMPTY;
    }

    return packetContent;
}

void Text2PcapWidget::on_pushButton_ParsePacket_clicked()
{
    /* 1、校验填充参数的合法性并获取相关参数 */
    if (!checkAndGetPadInfo()) {
        return;
    }

    /* 2、校验解析文件存储路径的合法性 */
    QString storagePath = ui->lineEdit_CapStoragePath->text();
    if (storagePath.isNull() || storagePath.isEmpty()) {
        QMessageBox::warning(this, UI_RES_CONTROL_MESSAGEBOX_WARNING, INFO_STRING_PCAP_SAVE_PATH_INVALID);
        return;
    }
    if (!FileUtils::isDir(storagePath)) {
        QMessageBox::warning(this, UI_RES_CONTROL_MESSAGEBOX_WARNING, INFO_STRING_PATH_IS_NOT_DIR);
        return;
    }
    m_parseConfig.storageFilePath = storagePath;

    /* 3、校验并转换为text2pcap格式 */
    QString packetContent = ui->textEdit_PacketContent->toPlainText();
    if (!m_parseConfig.hexDump) {
        QString packetContentTrimed = checkAndTrimParsePacketContent(packetContent);
        if (packetContentTrimed.isEmpty()) {
            return;
        }
        m_parseConfig.text2PcapPacketContent = WiresharkUtils::getTex2PcapFormatString(packetContentTrimed);
    } else {
        m_parseConfig.text2PcapPacketContent = packetContent;
    }
    m_parseConfig.dateTime = QDateTime::currentDateTime();

    /* 5、启动后续的信息加工 */
    Text2Pcap::StartProcess(m_parseConfig);
}

void Text2PcapWidget::on_pushButton_CleanAllCapFiles_clicked()
{
    QString storagePath = ui->lineEdit_CapStoragePath->text();
    if (storagePath.isNull() || storagePath.isEmpty()) {
        QMessageBox::warning(this, UI_RES_CONTROL_MESSAGEBOX_WARNING, INFO_STRING_PCAP_SAVE_PATH_INVALID);
        return;
    }
    if (!FileUtils::isDir(storagePath)) {
        QMessageBox::warning(this, UI_RES_CONTROL_MESSAGEBOX_WARNING, INFO_STRING_PATH_IS_NOT_DIR);
        return;
    }

    QMessageBox::StandardButton msgBox;
    msgBox = QMessageBox::question(this, UI_RES_CONTROL_MESSAGEBOX_WARNING, INFO_STRING_CONFIRM_DEL_PCAP_DIR, QMessageBox::Yes | QMessageBox::No);
    if (msgBox == QMessageBox::No) {
        return;
    }

    uint32_t filesNum = FileUtils::deleteFilesBySuffix(storagePath, FILE_EXTENTION_PCAP);
    filesNum += FileUtils::deleteFilesBySuffix(storagePath, FILE_EXTENTION_PCAPNG);
    QMessageBox::information(this, UI_RES_CONTROL_MESSAGEBOX_INFO, QString::asprintf(INFO_STRING_DEL_PCAP_DIR_OK, filesNum));
}

void Text2PcapWidget::on_pushButton_clearPacket_clicked()
{
    ui->textEdit_PacketContent->clear();
}

void Text2PcapWidget::on_pushButton_CopyPacket_clicked()
{
    QString source = ui->textEdit_PacketContent->toPlainText();
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(source);
}

void Text2PcapWidget::on_radioButton_No_Pad_clicked()
{
    ui->lineEdit_Link_Type_Value->setDisabled(true);
    ui->lineEdit_IPv4_Proto_Num_Value->setDisabled(true);
    ui->lineEdit_TCP_Src_Port_Value->setDisabled(true);
    ui->lineEdit_TCP_Dst_Port_Value->setDisabled(true);
    ui->lineEdit_UDP_Src_Port_Value->setDisabled(true);
    ui->lineEdit_UDP_Dst_Port_Value->setDisabled(true);

    m_parseConfig.padType = PAD_TYPE_NONE;
}

void Text2PcapWidget::on_radioButton_Pad_LinkLayer_clicked()
{
    ui->lineEdit_Link_Type_Value->setDisabled(false);
    ui->lineEdit_IPv4_Proto_Num_Value->setDisabled(true);
    ui->lineEdit_TCP_Src_Port_Value->setDisabled(true);
    ui->lineEdit_TCP_Dst_Port_Value->setDisabled(true);
    ui->lineEdit_UDP_Src_Port_Value->setDisabled(true);
    ui->lineEdit_UDP_Dst_Port_Value->setDisabled(true);

    m_parseConfig.padType = PAD_TYPE_LINK;
}

void Text2PcapWidget::on_radioButton_Pad_IPv4Layer_clicked()
{
    ui->lineEdit_Link_Type_Value->setDisabled(true);
    ui->lineEdit_IPv4_Proto_Num_Value->setDisabled(false);
    ui->lineEdit_TCP_Src_Port_Value->setDisabled(true);
    ui->lineEdit_TCP_Dst_Port_Value->setDisabled(true);
    ui->lineEdit_UDP_Src_Port_Value->setDisabled(true);
    ui->lineEdit_UDP_Dst_Port_Value->setDisabled(true);

    m_parseConfig.padType = PAD_TYPE_IPV4;
}

void Text2PcapWidget::on_radioButton_Pad_IPv6Layer_clicked()
{
    ui->lineEdit_Link_Type_Value->setDisabled(true);
    ui->lineEdit_IPv4_Proto_Num_Value->setDisabled(true);
    ui->lineEdit_TCP_Src_Port_Value->setDisabled(true);
    ui->lineEdit_TCP_Dst_Port_Value->setDisabled(true);
    ui->lineEdit_UDP_Src_Port_Value->setDisabled(true);
    ui->lineEdit_UDP_Dst_Port_Value->setDisabled(true);

    m_parseConfig.padType = PAD_TYPE_IPV6;
}

void Text2PcapWidget::on_radioButton_Pad_UDPLayer_clicked()
{
    ui->lineEdit_Link_Type_Value->setDisabled(true);
    ui->lineEdit_IPv4_Proto_Num_Value->setDisabled(true);
    ui->lineEdit_TCP_Src_Port_Value->setDisabled(true);
    ui->lineEdit_TCP_Dst_Port_Value->setDisabled(true);
    ui->lineEdit_UDP_Src_Port_Value->setDisabled(false);
    ui->lineEdit_UDP_Dst_Port_Value->setDisabled(false);

    m_parseConfig.padType = PAD_TYPE_UDP;
}

void Text2PcapWidget::on_radioButton_Pad_TCPLayer_clicked()
{
    ui->lineEdit_Link_Type_Value->setDisabled(true);
    ui->lineEdit_IPv4_Proto_Num_Value->setDisabled(true);
    ui->lineEdit_TCP_Src_Port_Value->setDisabled(false);
    ui->lineEdit_TCP_Dst_Port_Value->setDisabled(false);
    ui->lineEdit_UDP_Src_Port_Value->setDisabled(true);
    ui->lineEdit_UDP_Dst_Port_Value->setDisabled(true);

    m_parseConfig.padType = PAD_TYPE_TCP;
}

void Text2PcapWidget::on_radioButton_Packet_Content_Pad_Hex_Stream_clicked()
{
    m_parseConfig.hexDump = false;
}

void Text2PcapWidget::on_radioButton_Packet_Content_Pad_Hex_Dump_clicked()
{
    m_parseConfig.hexDump = true;
}


void Text2PcapWidget::on_radioButton_Output_Format_Pcap_clicked()
{
    m_parseConfig.saveFileSuffix = FILE_EXTENTION_PCAP;
}


void Text2PcapWidget::on_radioButton_Output_Format_PcapNG_clicked()
{
    m_parseConfig.saveFileSuffix = FILE_EXTENTION_PCAPNG;
}


void Text2PcapWidget::on_pushButton_CopyPacket2ClipBoard_clicked()
{
    QString packetContent = ui->textEdit_PacketContent->toPlainText();
    QClipboard *clipboard = QApplication::clipboard();
    QString originalText = clipboard->text();
    clipboard->setText(packetContent);
}

