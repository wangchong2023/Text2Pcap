#include "Main/initialize.h"
#include "Common/common_header.h"

void Initialize::LoadDefaultValue() {
    InitLog();
    Text2Pcap::Initialize();
}

void Initialize::LoadSysTray(Text2PcapWidget *win) {
    SysTray *systray = new SysTray(win);
    systray->show(UI_RES_STRING_DEFAULT_SYSTRAY_TITLE, UI_RES_STRING_DEFAULT_SYSTRAY_MSG);
}

void Initialize::LoadConnect() {

}

void Initialize::LoadControl(Text2PcapWidget *win) {
    win->setWindowFlags(Qt::Dialog);
    win->setFixedSize(UI_SIZE_WIDGET_WIDTH, UI_SIZE_WIDGET_HEIGHT);

    FontUtils::SetDefaultAppFont();
    FontUtils::SetDefaultToolTipFont();

    Ui::Text2PcapWidget *ui = win->ui;

    ui->textEdit_PacketContent->setFocus();

    ui->label_EmailValue->setOpenExternalLinks(true);
    ui->label_EmailValue->setText(UI_RES_STRING_DEFAULT_EMAIL_HREF);

    ui->label_VersionValue->setText(TEXT2CAP_VERSION);
    ui->label_BuildValue->setText(BuildUtils::getBuildDateTime());

    QString wiresharkPath = WiresharkUtils::geAppPathFromFile(APP_NAME_WIRESHARK);
    ui->lineEdit_WiresharkPath->setText(wiresharkPath);

    QString displayWiresharkPath = WiresharkUtils::geAppPathFromFile(APP_NAME_DISPLAY_WIRESHARK);
    if (!FileUtils::isFileExist(displayWiresharkPath)) {
        displayWiresharkPath = STRING_BLANK;
    }
    ui->lineEdit_WiresharkPath->setText(displayWiresharkPath);

    QString storageFilePath = WiresharkUtils::getPcapStoragePath();
    if (!FileUtils::isDirExist(storageFilePath)) {
        storageFilePath = STRING_BLANK;
    }
    ui->lineEdit_CapStoragePath->setText(storageFilePath);

    QString saveFileSuffix = WiresharkUtils::getPcapFormatValue();
    if (saveFileSuffix == FILE_EXTENTION_PCAP) {
        ui->radioButton_Output_Format_Pcap->setChecked(true);
    } else {
        ui->radioButton_Output_Format_PcapNG->setChecked(true);
    }

    win->setSysSetting2ParseParam(WiresharkUtils::getAppPathByDisplayWiresharkPath(APP_NAME_WIRESHARK, displayWiresharkPath),
                                  WiresharkUtils::getAppPathByDisplayWiresharkPath(APP_NAME_TEXT2CAP, displayWiresharkPath),
                                  storageFilePath, saveFileSuffix);

    ui->textEdit_PacketContent->setUndoRedoEnabled(true);

    ui->radioButton_Ethernet->setToolTip(INFO_STRING_TOOLTIP_PARSE_ETHERNET);
    ui->radioButton_No_Pad->setToolTip(INFO_STRING_TOOLTIP_TYPE_NO_PAD);
    ui->radioButton_Pad_LinkLayer->setToolTip(INFO_STRING_TOOLTIP_TYPE_PAD_LINK);
    ui->radioButton_Pad_IPv4Layer->setToolTip(INFO_STRING_TOOLTIP_TYPE_PAD_IP);
    ui->radioButton_Pad_TCPLayer->setToolTip(INFO_STRING_TOOLTIP_TYPE_PAD_TCP);
    ui->radioButton_Pad_UDPLayer->setToolTip(INFO_STRING_TOOLTIP_TYPE_PAD_UDP);

    ui->lineEdit_Link_Type_Value->setToolTip(INFO_STRING_TOOLTIP_LINK_TYPE_RANGE);
    ui->lineEdit_IPv4_Proto_Num_Value->setToolTip(INFO_STRING_TOOLTIP_IP_PROTO_NUM_RANGE);
    ui->lineEdit_TCP_Src_Port_Value->setToolTip(INFO_STRING_TOOLTIP_PORT_NUM_RANGE);
    ui->lineEdit_TCP_Dst_Port_Value->setToolTip(INFO_STRING_TOOLTIP_PORT_NUM_RANGE);
    ui->lineEdit_UDP_Src_Port_Value->setToolTip(INFO_STRING_TOOLTIP_PORT_NUM_RANGE);
    ui->lineEdit_UDP_Dst_Port_Value->setToolTip(INFO_STRING_TOOLTIP_PORT_NUM_RANGE);

    ui->radioButton_Packet_Content_Pad_Hex_Stream->setToolTip(INFO_STRING_TOOLTIP_CONTENT_TYPE_HEX_STREAM);
    ui->radioButton_Packet_Content_Pad_Hex_Dump->setToolTip(INFO_STRING_TOOLTIP_CONTENT_TYPE_HEX_DUMP);
    ui->textEdit_PacketContent->setToolTip(INFO_STRING_TOOLTIP_PACKET_CONTENT);

    ui->lineEdit_WiresharkPath->setToolTip(INFO_STRING_TOOLTIP_WIRESHARK_PATH);
    ui->lineEdit_CapStoragePath->setToolTip(INFO_STRING_TOOLTIP_PCAP_STORAGE_PATH);
}

void Initialize::LoadResources(Text2PcapWidget *win) {
    LoadDefaultValue();
    InitSetting();
    LoadSysTray(win);
    LoadConnect();
    LoadControl(win);
}

void Initialize::InitLog()
{
    qInstallMessageHandler(LogUtils::log);
}

void Initialize::InitSetting()
{
    QCoreApplication::setApplicationVersion(TEXT2CAP_VERSION);
    QCoreApplication::setOrganizationName(TEXT2CAP_ORG_NAME);
    QCoreApplication::setOrganizationDomain(TEXT2CAP_ORG_DOMAIN);
    QCoreApplication::setApplicationName(TEXT2CAP_APP_NAME);
}
