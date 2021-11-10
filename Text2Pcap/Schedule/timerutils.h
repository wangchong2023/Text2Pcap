#ifndef TIMERUTILS_H
#define TIMERUTILS_H

#include <QObject>
#include <QString>
#include <QTimer>
#include <QMap>
#include <QDebug>

#define TIMER_INVALID_TYPE      0
#define TIMER_INVALID_INTERVAL  0
#define TIMER_RESERVED_TYPE     0
#define TIMER_RESERVED_INTERVAL 0xFFFFFFFF
typedef void (*TIMER_CALLBACK)(void *parm);

typedef struct stTIMER_REGISTER_S {
    uint32_t timerType;
    QTimer* timer;
    bool repeat;
    uint32_t intervalMsec;
    TIMER_CALLBACK pfCallBack;
    void* data;
}TIMER_REGISTER_S;

class TimerUtils : public QObject
{
    Q_OBJECT
public:
    explicit TimerUtils(QObject *parent = nullptr);
    ~TimerUtils();

    static QMap<uint32_t, TIMER_REGISTER_S> InitializeTimerMap();
    static TIMER_REGISTER_S FindTimerByType(uint32_t timerType);
    static void RegisterTimer(TIMER_REGISTER_S &registerInfo);
    static void UnRegisterTimer(uint32_t timerType);
    static void StartTimer(uint32_t timerType);
    static void StopTimer(uint32_t timerType);

public slots:
     static void HandleTimeout(void *param);
private:
     static QMap<uint32_t, TIMER_REGISTER_S> timerMap;
};

#endif // TIMERUTILS_H
