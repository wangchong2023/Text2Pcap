#include "Schedule/timerutils.h"
#include "Common/common_def.h"
#include <QMap>

TimerUtils::TimerUtils(QObject *parent) : QObject(parent){
}

QMap<uint32_t, TIMER_REGISTER_S> TimerUtils::timerMap = InitializeTimerMap();

TimerUtils::~TimerUtils() {
    QMapIterator<uint32_t, TIMER_REGISTER_S> iterator(timerMap);
    while (iterator.hasNext()) {
        iterator.next();
        timerMap.remove(iterator.key());
        TIMER_REGISTER_S regInfo = iterator.value();
        if (regInfo.timer != nullptr) {
            delete regInfo.timer;
        }
    }
}

QMap<uint32_t, TIMER_REGISTER_S> TimerUtils::InitializeTimerMap() {
    TIMER_REGISTER_S registerInfo;
    registerInfo.intervalMsec = TIMER_RESERVED_INTERVAL;
    registerInfo.timer = nullptr;
    registerInfo.repeat = false;
    registerInfo.timerType = TIMER_RESERVED_TYPE;
    registerInfo.pfCallBack = nullptr;
    registerInfo.data = nullptr;

    timerMap.insert(registerInfo.timerType, registerInfo);

    return timerMap;
}

TIMER_REGISTER_S TimerUtils::FindTimerByType(uint32_t timerType) {
    return timerMap.value(timerType);
}

void TimerUtils::RegisterTimer(TIMER_REGISTER_S &registerInfo) {
    if (registerInfo.intervalMsec == TIMER_INVALID_INTERVAL) {
        qDebug("Register timer failed, for intervalMsec is invalid.\n");
        return;
    }

    if (registerInfo.pfCallBack == nullptr) {
        qDebug("Register timer failed, for pfCallBack is null.\n");
        return;
    }

    if (timerMap.contains(registerInfo.timerType)) {
        qDebug("Register timer failed, for timer type(type=%d) has alrady exist.\n", registerInfo.timerType);
        return;
    }

    timerMap.insert(registerInfo.timerType, registerInfo);
}

void TimerUtils::UnRegisterTimer(uint32_t timerType) {
    timerMap.remove(timerType);
}

void TimerUtils::HandleTimeout(void *param) {
    qDebug("Timer is out, call processing function.\n");

    TIMER_REGISTER_S* registerInfo = (TIMER_REGISTER_S*)param;
    if (param == nullptr) {
        qDebug("Timer is out, registerInfo is null.\n");
        return;
    }
    QTimer *timerPtr = (QTimer*)registerInfo->timer;
    if (timerPtr == nullptr) {
        qDebug("HandleTimeout timer is null.\n");
        return;
    }

    /* 一次性定时器超时后即停止 */
    if ((!registerInfo->repeat) && (timerPtr->isActive())) {
        timerPtr->stop();
        registerInfo->timer = nullptr;
    }
    if (registerInfo->pfCallBack != nullptr) {
        registerInfo->pfCallBack(registerInfo->data);
    }
}

void TimerUtils::StartTimer(uint32_t timerType) {
    qDebug("Start timer(type=%d)", timerType);

    TIMER_REGISTER_S registerInfo = FindTimerByType(timerType);
    QTimer *timer = registerInfo.timer;
    if (timer == nullptr) {
        qDebug("Start timer(type=%d) failed, for new QTimer error.\n", timerType);
        return;
    }

    if (!timer->isActive()) {
        timer->start(registerInfo.intervalMsec);
    }

    /* 增加连接 */
    connect(timer, &QTimer::timeout, [=]() {
         HandleTimeout((void*)(&registerInfo));
    });
}

void TimerUtils::StopTimer(uint32_t timerType) {
    qDebug("Stop timer(type=%d)", timerType);

    TIMER_REGISTER_S registerInfo = FindTimerByType(timerType);

    QTimer *timer = (QTimer*)registerInfo.timer;
    if (timer == nullptr) {
        qDebug("Stop timer(type=%d) failed, for can not find the timer type.\n", timerType);
        return;
    }

    if (timer->isActive()) {
        timer->stop();
    }

    registerInfo.timer = nullptr;

    /* 连接由Qt自行删除 */
}
