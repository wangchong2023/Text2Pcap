#ifndef LOGUTILS_H
#define LOGUTILS_H

#include <QDateTime>
#include <QFile>
#include <QMap>
#include <QObject>
#include <QString>
#include <QTextStream>
#include <qlogging.h>

#define LOG_INVALID_TYPE tr("ReservedLogType")

/** @brief 日志注册信息结构体 */
typedef struct stLOG_REGISTER_S {
  QString logType;      ///< 日志类型标识
  QString outputFormat; ///< 日志输出格式
  QString timeFormat;   ///< 时间戳格式
  QString filePath;     ///< 日志文件路径
} LOG_REGISTER_S;

/**
 * @class LogUtils
 * @brief 日志管理工具类，提供日志的注册、注销和格式化输出功能。
 *
 * 通过静态 logMap 管理多种日志类型，支持按类型注册不同的日志输出配置。
 * 使用 Qt 的消息处理机制进行日志拦截和输出。
 */
class LogUtils : public QObject {
  Q_OBJECT
public:
  explicit LogUtils(QObject *parent = nullptr);
  ~LogUtils();

  /** @brief 初始化日志映射表 */
  static QMap<QString, LOG_REGISTER_S *> InitializeLogMap();
  /** @brief 根据类型查找已注册的日志配置 */
  static LOG_REGISTER_S *FindLogByType(QString logType);
  /** @brief 注册新的日志配置（使用 new 分配，UnRegisterLog 中 delete 释放） */
  static void RegisterLog(LOG_REGISTER_S *registerInfo);
  /** @brief 注销指定类型的日志配置 */
  static void UnRegisterLog(QString logType);
  /** @brief Qt 消息处理回调，拦截并格式化日志输出 */
  static void log(QtMsgType type, const QMessageLogContext &context,
                  const QString &msg);

signals:
private:
  static QMap<QString, LOG_REGISTER_S *> logMap; ///< 日志类型 → 配置映射表
};

#endif // LOGUTILS_H
