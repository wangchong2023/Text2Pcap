#include "Common/common_header.h"
#include "Utils/Theme/qssstyle.h"

void QssStyle::setStyle(const QString &style) {
    QFile qss(style);
    qss.open(QFile::ReadOnly);
    qApp->setStyleSheet(qss.readAll());
    qss.close();
}
