#ifndef UI_HEADER_H
#define UI_HEADER_H
#include "Pages/text2pcapwidget.h"
#include "ui_text2pcapwidget.h"

/* 布局 */
#define UI_SIZE_WIDGET_WIDTH 800
#define UI_SIZE_WIDGET_HEIGHT 600

/* 资源文件 */
#define UI_RES_ICON_DEFAULT_APP ":/app/icons/icons/Design.png"
#define UI_RES_LANG_ZH_CN ":/lang/Lang_zh_CN.qm"
#define UI_RES_LANG_EN_GB ":/lang/Lang_en_GB.qm"
#define UI_RES_QSS_LANG_LIGHT ":/qss/theme/light.qss"
#define UI_RES_QSS_LANG_DARK ":/qss/theme/dark.qss"

/* 系统托盘 */
#define UI_RES_STRING_DEFAULT_SYSTRAY_MENTU_MIN tr("&Minimize")
#define UI_RES_STRING_DEFAULT_SYSTRAY_MENTU_QUIT tr("&Quit")
#define UI_RES_STRING_DEFAULT_SYSTRAY_MENTU_RESTORE tr("&Restore")
#define UI_RES_STRING_DEFAULT_SYSTRAY_TITLE tr("提示")
#define UI_RES_STRING_DEFAULT_SYSTRAY_MSG                                      \
  tr("尽情使用报文解析工具带给你的便捷吧！")
#define UI_RES_STRING_DEFAULT_EMAIL_HREF                                       \
  "<a href=\"mailto:wangchong@msn.com\">wangchong@msn.com"

/* 消息对话框 */
#define UI_RES_CONTROL_MESSAGEBOX_INFO tr("提示")
#define UI_RES_CONTROL_MESSAGEBOX_WARNING tr("警告")

/* 控件 */
#define UI_RES_CONTROL_TEXT2WIDGET_WS_DIAG_TITLE                               \
  tr("指定wireshark可执行文件路径")
#define UI_RES_CONTROL_TEXT2WIDGET_PCAP_DIAG_TITLE tr("指定pcap文件保存路径")

#endif // UI_HEADER_H
