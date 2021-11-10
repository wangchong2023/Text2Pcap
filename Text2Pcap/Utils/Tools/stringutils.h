#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <QObject>
#include <QRegularExpression>

class StringUtils : public QObject
{
    Q_OBJECT
public:
    explicit StringUtils(QObject *parent = nullptr);
    static bool IsDigit(char ch);
    static bool IsLetter(char ch);
    static bool IsHexLetter(char ch);
    static bool IsDigitOrLetter(char ch);
    static bool IsHex(char ch);
    static bool isHexString(QString str);
    static bool isDigitalString(QString str);
    static void TrimBlankString(QString& str);

    static QString Number2String(uint32_t number);
    static QString Dec2Number2FilledHexString(uint32_t numberDec, uint32_t fillWidth);
    static QString Dec2Number2HexString(uint32_t numberDec);

signals:

};

#endif // STRINGUTILS_H
