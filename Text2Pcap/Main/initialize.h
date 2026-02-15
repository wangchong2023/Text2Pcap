#ifndef INITIALIZE_H
#define INITIALIZE_H

#include "Pages/text2pcapwidget.h"
#include "Utils/System/systray.h"
#include <QObject>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui {
class Text2PcapWidget;
}
QT_END_NAMESPACE

/**
 * @class Initialize
 * @brief 应用启动初始化类，负责加载默认值、系统托盘、信号连接、控件和资源。
 */
class Initialize : public QObject {
  Q_OBJECT
public:
  /** @brief 加载默认配置值 */
  static void LoadDefaultValue();
  /** @brief 初始化系统托盘图标及菜单 */
  static void LoadSysTray(Text2PcapWidget *win);
  /** @brief 建立信号与槽连接 */
  static void LoadConnect();
  /** @brief 初始化界面控件状态 */
  static void LoadControl(Text2PcapWidget *ui);
  /** @brief 加载样式表等资源文件 */
  static void LoadResources(Text2PcapWidget *ui);
  /** @brief 初始化日志系统 */
  static void InitLog();
  /** @brief 初始化应用配置 */
  static void InitSetting();

private:
  // static SysTray *systray;
};

#endif // INITIALIZE_H
