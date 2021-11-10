#ifndef SYSRUN_H
#define SYSRUN_H

#include <QObject>

#define REG_RUN "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run"

class SysRun : public QObject
{
    Q_OBJECT
public:
    explicit SysRun(QObject *parent = nullptr);

signals:
public:
    void setAutoRun(bool isAutoRun);
};

#endif // SYSRUN_H
