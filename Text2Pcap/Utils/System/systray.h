#ifndef SYSTRAY_H
#define SYSTRAY_H

#include "Common/sys_header.h"
#include "Common/ui_header.h"

class SysTray : public QObject
{
    Q_OBJECT
public:
    SysTray(QWidget *parent);
    SysTray(QWidget *parent, QIcon& icon, QString& tips);

signals:

private slots:
    void onActivated(QSystemTrayIcon::ActivationReason reason);
    void messageClicked();
    void showMessage();

private:
    QWidget *m_parent;
    QSystemTrayIcon *m_systray;
    QMenu *m_trayMenu;

    QAction *m_minAction;
    QAction *m_quitAction;
    QAction *m_restoreAction;

private:
    void createDefaultActions();
    void createDefaultTrayIcon();
    void createTrayIcon(QIcon& icon, QString& tips);

public:
    void show(const QString &title, const QString &msg);
};

#endif // SYSTRAY_H
