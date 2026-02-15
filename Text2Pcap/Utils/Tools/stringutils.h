#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <QObject>
#include <QRegularExpression>

/**
 * @class StringUtils
 * @brief 字符串处理工具类，提供字符类型判断、字符串校验和数制转换等功能。
 */
class StringUtils : public QObject {
  Q_OBJECT
public:
  explicit StringUtils(QObject *parent = nullptr);

  /** @brief 判断字符是否为十进制数字 ('0'-'9') */
  static bool IsDigit(char ch);
  /** @brief 判断字符是否为字母 ('a'-'z', 'A'-'Z') */
  static bool IsLetter(char ch);
  /** @brief 判断字符是否为十六进制字母 ('a'-'f', 'A'-'F') */
  static bool IsHexLetter(char ch);
  /** @brief 判断字符是否为数字或字母 */
  static bool IsDigitOrLetter(char ch);
  /** @brief 判断字符是否为合法十六进制字符（数字或十六进制字母） */
  static bool IsHex(char ch);
  /** @brief 校验字符串是否全部由合法十六进制字符组成 */
  static bool isHexString(QString str);
  /** @brief 校验字符串是否为合法的十六进制数字字符串（注意：实际验证十六进制）
   */
  static bool isDigitalString(QString str);
  /** @brief 去除字符串中的空白字符 */
  static void TrimBlankString(QString &str);

  /** @brief 无符号整数转字符串 */
  static QString Number2String(uint32_t number);
  /** @brief 十进制数转指定宽度的十六进制字符串（前导零填充） */
  static QString Dec2Number2FilledHexString(uint32_t numberDec,
                                            uint32_t fillWidth);
  /** @brief 十进制数转十六进制字符串 */
  static QString Dec2Number2HexString(uint32_t numberDec);

signals:
};

#endif // STRINGUTILS_H
