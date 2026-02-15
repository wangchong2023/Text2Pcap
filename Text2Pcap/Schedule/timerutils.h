#ifndef TIMERUTILS_H
#define TIMERUTILS_H

#include <QDebug>
#include <QMap>
#include <QObject>
#include <QString>
#include <QTimer>

#define TIMER_INVALID_TYPE 0
#define TIMER_INVALID_INTERVAL 0
#define TIMER_RESERVED_TYPE 0
#define TIMER_RESERVED_INTERVAL 0xFFFFFFFF
/** @brief 定时器回调函数类型 */
typedef void (*TIMER_CALLBACK)(void *parm);

/** @brief 定时器注册信息结构体 */
typedef struct stTIMER_REGISTER_S {
  uint32_t timerType;        ///< 定时器类型标识
  QTimer *timer;             ///< Qt定时器指针
  bool repeat;               ///< 是否重复触发
  uint32_t intervalMsec;     ///< 触发间隔（毫秒）
  TIMER_CALLBACK pfCallBack; ///< 超时回调函数
  void *data;                ///< 回调参数数据
} TIMER_REGISTER_S;

/**
 * @class TimerUtils
 * @brief 定时器管理工具类，提供定时器的注册、启动、停止和超时处理功能。
 *
 * 通过静态 timerMap 管理所有定时器实例，支持按类型查找和操作。
 */
class TimerUtils : public QObject {
  Q_OBJECT
public:
  explicit TimerUtils(QObject *parent = nullptr);
  ~TimerUtils();

  /** @brief 初始化定时器映射表 */
  static QMap<uint32_t, TIMER_REGISTER_S> InitializeTimerMap();
  /** @brief 根据类型查找已注册的定时器 */
  static TIMER_REGISTER_S FindTimerByType(uint32_t timerType);
  /** @brief 注册一个新定时器 */
  static void RegisterTimer(TIMER_REGISTER_S &registerInfo);
  /** @brief 注销指定类型的定时器 */
  static void UnRegisterTimer(uint32_t timerType);
  /** @brief 启动指定类型的定时器 */
  static void StartTimer(uint32_t timerType);
  /** @brief 停止指定类型的定时器 */
  static void StopTimer(uint32_t timerType);

public slots:
  /** @brief 定时器超时处理槽函数 */
  static void HandleTimeout(void *param);

private:
  static QMap<uint32_t, TIMER_REGISTER_S> timerMap;
};

#endif // TIMERUTILS_H
