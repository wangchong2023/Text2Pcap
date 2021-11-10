#ifndef PROCESSUTILS_H
#define PROCESSUTILS_H

#include <QObject>
#include <QStringList>

class ProcessUtils : public QObject
{
    Q_OBJECT
public:
    explicit ProcessUtils(QObject *parent = nullptr);
    static bool StartDetachedProcess(QString program, QStringList argsList, int waitTime);

signals:

};

#endif // PROCESSUTILS_H
