#include <singleapplication.h>
#include <QLocale>
#include <QTranslator>
#include "Main/initialize.h"

int main(int argc, char *argv[])
{
    SingleApplication app(argc, argv);
    Text2PcapWidget win;

    /* 单实例模式 */
    QObject::connect(&app, &SingleApplication::instanceStarted, [&win]() {
            win.raise();
            win.activateWindow();
        });

    /* 资源初始化 */
    Initialize::LoadResources(&win);

    win.show();

    return app.exec();
}
