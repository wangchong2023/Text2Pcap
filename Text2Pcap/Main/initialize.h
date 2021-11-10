#ifndef INITIALIZE_H
#define INITIALIZE_H

#include <QObject>
#include <QString>
#include "Pages/text2pcapwidget.h"
#include "Utils/System/systray.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Text2PcapWidget; }
QT_END_NAMESPACE

class Initialize : public QObject
{
    Q_OBJECT
public:
    static void LoadDefaultValue();
    static void LoadSysTray(Text2PcapWidget *win);
    static void LoadConnect();
    static void LoadControl(Text2PcapWidget *ui);
    static void LoadResources(Text2PcapWidget *ui);
    static void InitLog();
    static void InitSetting();
private:
    //static SysTray *systray;
};

#endif // INITIALIZE_H
