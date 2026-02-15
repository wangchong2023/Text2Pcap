#include "wiresharkutils.h"
#include "Common/common_def.h"
#include "Common/infostring.h"
#include "Common/ui_header.h"
#include "Utils/MultiPlatform/Common/common_adaptor.h"
#include "Utils/MultiPlatform/MacOS/wiresharkutils_macos.h"
#include "Utils/MultiPlatform/Windows/wiresharkutils_win.h"
#include "Utils/Tools/stringutils.h"
#include <iomanip>
#include <sstream>

WiresharkUtils::WiresharkUtils(QObject *parent) : QObject(parent) {}

bool WiresharkUtils::isWiresharkPathValid(QString displayCustomedWiresharkPath,
                                          QString &codeStr) {
  if (!FileUtils::isFileExist(displayCustomedWiresharkPath)) {
    codeStr = INFO_STRING_SAVE_DIR_FAILED;
    return false;
  }

  QString appName = FileUtils::getAppNameByPath(displayCustomedWiresharkPath);
  if (appName.isNull() || appName.isEmpty()) {
    codeStr = INFO_STRING_GET_FILE_NAME_FAILED;
    return false;
  }

  if (!isValidWiresharkFileName(appName)) {
    codeStr = INFO_STRING_FILE_IS_NOT_WIRESHARK;
    return false;
  }

  return true;
}

void WiresharkUtils::writeWiresharkPathConfig(
    QString displayCustomedWiresharkPath) {
  QString wiresharkPath = FileUtils::GetSubAppPathByAppAndSubName(
      displayCustomedWiresharkPath, APP_NAME_WIRESHARK);
  QSettings setting(getSettingPath(), QSettings::IniFormat);
  setting.setValue(WIRESHARK_CUSTOMED_CONFIG, wiresharkPath);
  setting.setValue(WIRESHARK_CUSTOMED_DISPLAY_CONFIG,
                   displayCustomedWiresharkPath);
  qDebug("Write wiershark path config(%s) to path(%s).",
         qPrintable(wiresharkPath), qPrintable(setting.fileName()));
  qDebug("Write wiershark display path config(%s) to path(%s).",
         qPrintable(wiresharkPath), qPrintable(setting.fileName()));
}

void WiresharkUtils::writePcapStoragePathConfig(QString pcapStoragePath) {
  QSettings setting(getSettingPath(), QSettings::IniFormat);
  setting.setValue(WIRESHARK_PCAP_STORAGE_CONFIG, pcapStoragePath);
  qDebug("Write pcap storage path config(%s) to path(%s).",
         qPrintable(pcapStoragePath), qPrintable(setting.fileName()));
  qDebug() << setting.fileName();
}

void WiresharkUtils::writePcapFormatConfig(QString pcapFormat) {
  QSettings setting(getSettingPath(), QSettings::IniFormat);
  setting.setValue(WIRESHARK_PCAP_Format_CONFIG, pcapFormat);
  qDebug("Write pcap format config(%s) to path(%s).", qPrintable(pcapFormat),
         qPrintable(setting.fileName()));
  qDebug() << setting.fileName();
}

QString WiresharkUtils::getUsingDisplayWiresharkPath(
    QString customedDisplayWiresharkPath,
    QString detectedDisplayWiresharkPath) {
  QString displayWiresharkPath = STRING_EMPTY;
  if (!customedDisplayWiresharkPath.isNull() &&
      (FileUtils::isFileExist(customedDisplayWiresharkPath))) {
    displayWiresharkPath = customedDisplayWiresharkPath;
  } else if (!detectedDisplayWiresharkPath.isEmpty() &&
             (FileUtils::isFileExist(detectedDisplayWiresharkPath))) {
    displayWiresharkPath = detectedDisplayWiresharkPath;
  }

  qDebug("Get wiershark display path(%s).", qPrintable(displayWiresharkPath));

  return displayWiresharkPath;
}

QString WiresharkUtils::geAppPathFromFile(QString appName) {
  if (!isAppNameSupport(appName)) {
    return STRING_EMPTY;
  }

  QString appPath;
  QString usingDisplayWiresharkPath = getUsingDisplayWiresharkPath();
  if (appName.compare(APP_NAME_DISPLAY_WIRESHARK) == 0) {
    appPath = usingDisplayWiresharkPath;
  } else {
    appPath = FileUtils::GetSubAppPathByAppAndSubName(usingDisplayWiresharkPath,
                                                      appName);
  }

  qDebug("Get %s path(%s).", qPrintable(appName), qPrintable(appPath));

  return appPath;
}

QString WiresharkUtils::getUsingDisplayWiresharkPath() {
  QSettings setting(getSettingPath(), QSettings::IniFormat);
  QString customedDisplayWiresharkPath =
      setting.value(WIRESHARK_CUSTOMED_DISPLAY_CONFIG).toString();
  QString detectedDisplayWiresharkPath =
      WiresharkUtils::geAppPath(APP_NAME_WIRESHARK);

  return getUsingDisplayWiresharkPath(customedDisplayWiresharkPath,
                                      detectedDisplayWiresharkPath);
}

QString
WiresharkUtils::getAppPathByDisplayWiresharkPath(QString appName,
                                                 QString wiresharkDisplayPath) {
  if (!isAppNameSupport(appName)) {
    return STRING_EMPTY;
  }

  return FileUtils::GetSubAppPathByAppAndSubName(wiresharkDisplayPath, appName);
}

QString WiresharkUtils::getPcapStoragePath() {
  QString settingPath = getSettingPath();

  QSettings configSaved(settingPath, QSettings::IniFormat);
  QString pcapStoragePath =
      configSaved.value(WIRESHARK_PCAP_STORAGE_CONFIG).toString();

  qDebug("Get pcap storage path config(%s) from path(%s).",
         qPrintable(pcapStoragePath), qPrintable(configSaved.fileName()));

  return pcapStoragePath;
}

QString WiresharkUtils::getPcapFormatValue() {
  QString settingPath = getSettingPath();

  QSettings configSaved(settingPath, QSettings::IniFormat);
  QString pcapFormat =
      configSaved.value(WIRESHARK_PCAP_Format_CONFIG).toString();

  qDebug("Get pcap format config(%s) from path(%s).", qPrintable(pcapFormat),
         qPrintable(configSaved.fileName()));

  return pcapFormat;
}

bool WiresharkUtils::isAppNameSupport(QString appName) {
  /* 不支持的类型返回空串 */
  if (appName.compare(APP_NAME_WIRESHARK) &&
      appName.compare(APP_NAME_TEXT2CAP) &&
      appName.compare(APP_NAME_DISPLAY_WIRESHARK)) {
    return false;
  }

  return true;
}

QString WiresharkUtils::getTex2PcapFormatString(QString strPacketContent) {
  if (strPacketContent.isNull() || strPacketContent.isEmpty()) {
    return STRING_EMPTY;
  }

  /* 转换为text2pcap格式
   * 000000 00 0e b6 00 00 02 00 0e b6 00 00 01 08 00 45 00
     000010 00 28 00 00 00 00 ff 01 37 d1 c0 00 02 01 c0 00
     000020 02 02 08 00 a6 2f 00 01 00 01 48 65 6c 6c 6f 20
     000030 57 6f 72 6c 64 21
     000036
  */
  QString text2capString;
  QString offsetFirst =
      StringUtils::Dec2Number2FilledHexString(0, WIRESHARK_TEXT2CAP_FILL_WIDTH);
  text2capString.append(offsetFirst).append(STRING_BLANK);

  int length = strPacketContent.length();
  if (length <= 0) {
    return STRING_EMPTY;
  }

  for (int i = 0; i < length; i++) {
    /* 追加字符 */
    char ch = strPacketContent.at(i).toLatin1();
    text2capString.append(ch);

    /* 每1个字节（2个16进制字符）追加空格 */
    if ((i + 1) % TEXT2CAP_SEP_CHAR_NUM == 0) {
      text2capString.append(STRING_BLANK);
    }

    /* 非首行每隔16个字节（32个16进制字符）去除尾部空格、追加回车换行 */
    if ((i + 1) % TEXT2CAP_LINE_CHAR_NUM == 0) {
      text2capString.chop(sizeof(char));
      text2capString.append(STRING_CRLF);

      /* 每行开始追加偏移值 */
      QString offset = StringUtils::Dec2Number2FilledHexString(
          ((i + 1) / TEXT2CAP_BYTE_TO_CHARS_NUM),
          WIRESHARK_TEXT2CAP_FILL_WIDTH);
      text2capString.append(offset).append(STRING_BLANK);
    }
  }

  /* 去除尾部空格 */
  if (text2capString.at(length - 1).toLatin1() == STRING_CHAR_BLANK) {
    text2capString.chop(sizeof(char));
  }

  /* 最后一行追加回车 */
  text2capString.append(STRING_CRLF);

  /* 最后一行追加偏移值 */
  text2capString.append(StringUtils::Dec2Number2FilledHexString(
      (strPacketContent.length() / TEXT2CAP_BYTE_TO_CHARS_NUM),
      WIRESHARK_TEXT2CAP_FILL_WIDTH));

  return text2capString;
}

QString WiresharkUtils::getTex2PcapFormatStringNew(QString strPacketContent) {
  if (strPacketContent.isNull() || strPacketContent.isEmpty()) {
    return STRING_EMPTY;
  }

  /* 转换为text2pcap格式
   * 000000 00 0e b6 00 00 02 00 0e b6 00 00 01 08 00 45 00
     000010 00 28 00 00 00 00 ff 01 37 d1 c0 00 02 01 c0 00
     000020 02 02 08 00 a6 2f 00 01 00 01 48 65 6c 6c 6f 20
     000030 57 6f 72 6c 64 21
     000036
  */

  const uint32_t colNumFix = 16;
  uint32_t row, col;
  std::stringstream dataStream;
  dataStream << std::hex;
  uint8_t *byteArr = (uint8_t *)(strPacketContent.toLatin1().data());
  uint32_t byteArrSize = strPacketContent.length();

  for (row = 0; row < byteArrSize; row += colNumFix) {
    dataStream << std::setw(WIRESHARK_TEXT2CAP_FILL_WIDTH)
               << std::setfill(STRING_CHAR_ZERO) << row << STRING_CHAR_BLANK;
    for (col = 0; col < colNumFix; col++) {
      if (row + col < byteArrSize) {
        dataStream << std::setw(2) << std::setfill(STRING_CHAR_ZERO)
                   << (int)byteArr[row + col] << STRING_CHAR_BLANK;
      }
    }
    dataStream << STRING_CRLF;
  }

  return dataStream.str().c_str();
}

/*
 * 文件路径示意：
 * /tmp/pcapfile_202111081400123.txt
 * /download/pcapfile_202111081400123.pcap
 */
QString WiresharkUtils::getParseFileName(QString rootPath,
                                         QDateTime curDateTime, QString prefix,
                                         QString suffix) {
  QString curDateTimeString =
      curDateTime.toString(TIME_FORMAT_SIMPLE_MSEC_UNDERLINE);
  QString filePath = rootPath + QDir::separator() + prefix + FILE_NAME_PREFIX +
                     FILE_SEP_UNDERLINE + curDateTimeString + FILE_SUFFIX_DOT +
                     suffix;
  QString fileCanonicalPath = QFileInfo(filePath).absoluteFilePath();

  return fileCanonicalPath;
}

QString WiresharkUtils::getHex2DumpTextFileName(QString prefix,
                                                QDateTime curDateTime) {
  return getParseFileName(QDir::tempPath(), curDateTime, prefix,
                          FILE_EXTENTION_TXT);
}

QString WiresharkUtils::getPcapFileName(QString rootPath, QDateTime curDateTime,
                                        QString prefix, QString suffix) {
  return getParseFileName(rootPath, curDateTime, prefix, suffix);
}

QString WiresharkUtils::geAppPath(QString appName) {
#ifdef Q_OS_MACOS
  return WiresharkUtilsMacOS::geAppPath(appName);
#endif

#ifdef Q_OS_WIN
  return WiresharkUtilsWin::geAppPath(appName);
#endif

  return QString(STRING_EMPTY);
}

QString WiresharkUtils::getSettingPath() {
  QString path = QDir::toNativeSeparators(
      QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation) +
      "/" + CONFIG_FILE_NAME);
  return path;
}
bool WiresharkUtils::isValidWiresharkFileName(QString appName) {
#ifdef Q_OS_MACOS
  return WiresharkUtilsMacOS::isValidWiresharkFileName(appName);
#endif

#ifdef Q_OS_WIN
  return WiresharkUtilsWin::isValidWiresharkFileName(appName);
#endif
}
