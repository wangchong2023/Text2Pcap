#include "Utils/Theme/qssstyle.h"
#include "Common/common_header.h"

void QssStyle::setStyle(const QString &style) {
  QFile qss(style);
  if (!qss.open(QFile::ReadOnly)) {
    return;
  }
  qApp->setStyleSheet(qss.readAll());
  qss.close();
}
