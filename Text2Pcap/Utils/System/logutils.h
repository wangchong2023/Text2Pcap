#ifndef LOGUTILS_H
#define LOGUTILS_H

#include <QObject>
#include <qlogging.h>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QMap>

#define LOG_INVALID_TYPE     tr("ReservedLogType")

typedef struct stLOG_REGISTER_S {
    QString logType;
    QString outputFormat;
    QString timeFormat;
    QString filePath;
}LOG_REGISTER_S;

class LogUtils : public QObject
{
    Q_OBJECT
public:
    explicit LogUtils(QObject *parent = nullptr);
    ~LogUtils();

    static QMap<QString, LOG_REGISTER_S*> InitializeLogMap();
    static LOG_REGISTER_S* FindLogByType(QString logType);
    static void RegisterLog(LOG_REGISTER_S* registerInfo);
    static void UnRegisterLog(QString logType);
    static void log(QtMsgType type, const QMessageLogContext &context, const QString &msg);

signals:
private:
    static QMap<QString, LOG_REGISTER_S*> logMap;
};

#endif // LOGUTILS_H
