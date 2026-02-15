#include "processutils.h"
#include <QProcess>

ProcessUtils::ProcessUtils(QObject *parent) : QObject(parent) {}

bool ProcessUtils::StartDetachedProcess(QString program, QStringList argsList,
                                        int waitTime) {
  Q_UNUSED(waitTime);
  return QProcess::startDetached(program, argsList);
}
