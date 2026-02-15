#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <QFile>
#include <QObject>
#include <QTextStream>

#include "Utils/MultiPlatform/MacOS/fileutils_macos.h"
#include "Utils/MultiPlatform/Windows/fileutils_win.h"

/**
 * @class FileUtils
 * @brief 跨平台文件与目录操作工具类。
 *
 * 提供路径解析、文件存在性检查、文件读写、删除和移至回收站等功能。
 * 平台差异通过 fileutils_macos.h / fileutils_win.h 桥接。
 */
class FileUtils : public QObject {
  Q_OBJECT
public:
  explicit FileUtils(QObject *parent = nullptr);

  /** @brief 从应用路径提取根目录 */
  static QString GetRootDirByAppPath(QString appPath);
  /** @brief 由根目录和子应用名组合完整路径 */
  static QString GetSubAppPathByRootAndSubName(QString rootDir,
                                               QString subAppName);
  /** @brief 由应用路径和子应用名组合完整路径 */
  static QString GetSubAppPathByAppAndSubName(QString appPath,
                                              QString subAppPath);
  /** @brief 判断路径是否为文件 */
  static bool isFile(QString filePath);
  /** @brief 判断路径是否为目录 */
  static bool isDir(QString dirPath);
  /** @brief 判断文件是否存在 */
  static bool isFileExist(QString appPath);
  /** @brief 判断目录是否存在 */
  static bool isDirExist(QString dirPath);
  /** @brief 从完整路径中提取文件名 */
  static QString getAppNameByPath(QString appPath);
  /** @brief 获取规范化路径 */
  static QString getAppCanonicalByPath(QString appPath);
  /** @brief 获取文件后缀名 */
  static QString getAppSuffixByPath(QString appPath);
  /** @brief 获取文件绝对路径 */
  static QString getAppAbsoluteByPath(QString appPath);
  /** @brief 将文本内容写入指定文件 */
  static void writeText2File(QString textPath, QString text);
  /** @brief 删除指定文件 */
  static void deleteFile(QString filePath);
  /** @brief 将目录下指定后缀的文件移入回收站，返回处理数量 */
  static uint32_t moveFiles2TrashBySuffix(QString dirPath, QString suffix);

signals:
};

#endif // FILEUTILS_H
