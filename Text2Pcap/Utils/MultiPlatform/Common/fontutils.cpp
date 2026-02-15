#include "fontutils.h"
#include "Utils/MultiPlatform/Common/common_adapter_def.h"
#include <QToolTip>
#include <singleapplication.h>

FontUtils::FontUtils(QObject *parent) : QObject(parent) {}

void FontUtils::SetAppFont(QString family, int pixelSize) {
  QFont font;
  font.setFamily(family);
  font.setPixelSize(pixelSize);
  qApp->setFont(font);
}

void FontUtils::SetDefaultAppFont() {
  SetAppFont(FONT_NAME_DEFAULT, FONT_SIZE_DEFAULT);
}

void FontUtils::SetToolTipFont(QString family, int pixelSize) {
  QFont font;
  font.setFamily(family);
  font.setPixelSize(pixelSize);
  QToolTip::setFont(font);
}

void FontUtils::SetDefaultToolTipFont() {
  SetToolTipFont(FONT_NAME_DEFAULT, FONT_SIZE_DEFAULT);
}
