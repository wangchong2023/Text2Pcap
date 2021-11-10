#include "processutils.h"
#include <QProcess>

ProcessUtils::ProcessUtils(QObject *parent) : QObject(parent)
{
}

bool ProcessUtils::StartDetachedProcess(QString program, QStringList argsList, int waitTime) {
    QProcess process;

    process.setProgram(program);
    process.setArguments(argsList);

    bool success;
    success = process.startDetached();
    if (!success) {
        return false;
    }
    success = process.waitForStarted(waitTime);
    if (!success) {
        return false;
    }

    return true;
}
