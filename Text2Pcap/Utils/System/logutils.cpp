#include "logutils.h"
#include "Common/common_header.h"

LogUtils::LogUtils(QObject *parent) : QObject(parent)
{

}

LogUtils::~LogUtils() {
    QMapIterator<QString, LOG_REGISTER_S*> iterator(logMap);
    while (iterator.hasNext()) {
        iterator.next();
        logMap.remove(iterator.key());
    }
}

QMap<QString, LOG_REGISTER_S*> LogUtils::logMap = InitializeLogMap();


QMap<QString, LOG_REGISTER_S*> LogUtils::InitializeLogMap() {

    return logMap;
}

LOG_REGISTER_S* LogUtils::FindLogByType(QString logType) {
    return (LOG_REGISTER_S*)logMap.value(logType);
}

void LogUtils::RegisterLog(LOG_REGISTER_S* registerInfo) {
    if (registerInfo == nullptr) {
        qDebug("Register log failed, for registerinfo is null.\n");
        return;
    }

    if (registerInfo->logType.isEmpty()) {
        qDebug("Register log failed, for log type is invalid.\n");
        return;
    }

    if (registerInfo->outputFormat.isEmpty()) {
        qDebug("Register log failed, for output format is invalid.\n");
        return;
    }

    if (registerInfo->timeFormat.isEmpty()) {
        qDebug("Register log failed, for times format is invalid.\n");
        return;
    }

    if ((registerInfo->filePath.isEmpty()) || (!FileUtils::isFileExist(registerInfo->filePath))) {
        qDebug("Register log failed, for file path is invalid.\n");
        return;
    }

    LOG_REGISTER_S* registerInfoNew = (LOG_REGISTER_S*)malloc(sizeof(LOG_REGISTER_S));
    registerInfoNew->logType = registerInfo->logType;
    registerInfoNew->outputFormat = registerInfo->outputFormat;
    registerInfoNew->timeFormat = registerInfo->timeFormat;
    registerInfoNew->filePath = registerInfo->filePath;

    logMap.insert(registerInfo->logType, registerInfoNew);
}

void LogUtils::UnRegisterLog(QString logType) {
    LOG_REGISTER_S* registerInfo = FindLogByType(logType);
    if (registerInfo == nullptr) {
        qDebug("Unregister log(type=%s) failed, for can not find the log type.\n", qPrintable(logType));
        return;
    }

    logMap.remove(logType);
    free(registerInfo);
}

void LogUtils::log(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
     static QMutex mutex;
     mutex.lock();
     QString text;

     switch(type)
     {
        case QtDebugMsg:
         text = QString("Debug:");
         break;
        case QtWarningMsg:
         text = QString("Warning:");
         break;
        case QtCriticalMsg:
         text = QString("Critical:");
         break;
        case QtFatalMsg:
         text = QString("Fatal:");
         break;
        default:
         break;
     }

     // 设置输出信息格式
     QString context_info = QString(LOG_OUTPUT_FORMAT_FL).arg(QString(context.file)).arg(context.line);
     QString strDateTimeDay = QDateTime::currentDateTime().toString(TIME_FORMAT_SIMPLE_DAY);
     QString strDateTime = QDateTime::currentDateTime().toString(TIME_FORMAT_SIMPLE_MSEC);
     QString strMessage = QString("%1 %2 \t%3 \t%4").arg(text).arg(context_info).arg(strDateTime).arg(msg);

     QFile file(QCoreApplication::applicationDirPath() + LOG_DIR + QString(strDateTimeDay.append(FILE_SUFFIX_DOT_LOG)));
     file.open(QIODevice::ReadWrite | QIODevice::Append);
     QTextStream stream(&file);
     stream << strMessage << STRING_CRLF;
     file.flush();
     file.close();

     mutex.unlock();
 }
