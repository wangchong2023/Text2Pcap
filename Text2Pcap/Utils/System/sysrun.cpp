#include "sysrun.h"
#include "Common/common_header.h"

SysRun::SysRun(QObject *parent) : QObject(parent)
{

}

void SysRun::setAutoRun(bool isAutoRun)
{
    QString appName = QApplication::applicationName();
    QSettings *settings = new QSettings(REG_RUN, QSettings::IniFormat);
    if (isAutoRun) {
        QString application_path = QApplication::applicationFilePath();
        settings->setValue(appName, application_path.replace("/", "\\"));
    } else {
        settings->remove(appName);
    }

    delete settings;
    settings = NULL;
}
