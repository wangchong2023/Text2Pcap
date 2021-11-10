#include "Utils/System/systray.h"

SysTray::SysTray(QWidget *parent)
{
    m_parent = parent;
    createDefaultActions();
    createDefaultTrayIcon();
}

SysTray::SysTray(QWidget *parent, QIcon& icon, QString& tips)
{
    m_parent = parent;

    createDefaultActions();
    createTrayIcon(icon, tips);
}

void SysTray::createDefaultActions()
{
    m_minAction = new QAction(tr("&Minimize"), m_parent);
    m_parent->connect(m_minAction, &QAction::triggered, m_parent, &QWidget::hide);

    m_restoreAction = new QAction(tr("&Restore"), m_parent);
    m_parent->connect(m_restoreAction, &QAction::triggered, m_parent, &QWidget::showNormal);

    m_quitAction = new QAction(tr("&Quit"), m_parent);
    m_parent->connect(m_quitAction, &QAction::triggered, m_parent, &QCoreApplication::quit);

//    m_parent->connect(m_systray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
//                      m_parent, SLOT(onActivated(QSystemTrayIcon::ActivationReason)));
}

void SysTray::createTrayIcon(QIcon& icon, QString& tips)
{
    createDefaultTrayIcon();

    m_systray->setIcon(icon);
    m_systray->setToolTip(tips);
}

void SysTray::createDefaultTrayIcon()
{
    m_trayMenu = new QMenu(m_parent);
    m_trayMenu->addAction(m_minAction);
    m_trayMenu->addAction(m_restoreAction);
    m_trayMenu->addAction(m_quitAction);
    m_trayMenu->addSeparator();

    m_systray = new QSystemTrayIcon(m_parent);
    m_systray->setContextMenu(m_trayMenu);
    m_systray->setIcon(QIcon(UI_RES_ICON_DEFAULT_APP));
    m_systray->setToolTip(UI_RES_STRING_DEFAULT_SYSTRAY_TITLE);
}

void SysTray::show(const QString &title, const QString &msg)
{
    m_systray->show();
    m_systray->showMessage(title, msg);
}

void SysTray::onActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
        QMessageBox::information(nullptr, "Trigger", "Trigger");
        break;
    case QSystemTrayIcon::DoubleClick:
        QMessageBox::information(nullptr, "DoubleClick", "DoubleClick");
        break;
    case QSystemTrayIcon::MiddleClick:
        break;
    default:
        ;
    }
}

void SysTray::messageClicked()
{
    QMessageBox::information(nullptr, tr("Systray"),
                             tr("Sorry, I already gave what help I could.\n"
                                "Maybe you should try asking a human?"));
}

void SysTray::showMessage()
{
    m_systray->showMessage(tr("Information"),
        tr("There is a new message!"),
        QSystemTrayIcon::MessageIcon::Information,
        5000);
}
