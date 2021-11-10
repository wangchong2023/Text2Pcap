#include "stringutils.h"
#include "Common/common_def.h"

StringUtils::StringUtils(QObject *parent) : QObject(parent)
{

}
bool StringUtils::IsDigit(char ch) {
    return ((ch >= '0') && (ch <= '9'));
}
bool StringUtils::IsLetter(char ch) {
    return (((ch >= 'A') && (ch <= 'Z')) || ((ch >= 'a') && (ch <= 'z')));
}
bool StringUtils::IsHexLetter(char ch) {
    return (((ch >= 'A') && (ch <= 'F')) || ((ch >= 'a') && (ch <= 'f')));
}
bool StringUtils::IsDigitOrLetter(char ch) {
    return (IsDigit(ch) || IsLetter(ch));
}
bool StringUtils::IsHex(char ch) {
    return (IsDigit(ch) || IsHexLetter(ch));
}

bool StringUtils::isHexString(QString str) {
    QByteArray byteArray = str.toLatin1();
    const char *chars = byteArray.data();
    while (*chars) {
        if (!IsHex(*chars)) {
            return false;
        }

        chars++;
    }

    return true;
}

bool StringUtils::isDigitalString(QString str) {
    QByteArray byteArray = str.toLatin1();
    const char *chars = byteArray.data();
    while (*chars) {
        if (!IsHex(*chars)) {
            return false;
        }

        chars++;
    }

    return true;
}

void StringUtils::TrimBlankString(QString& str) {
    str.remove(QRegularExpression(REG_EXPRESS_BLANK));
}

QString StringUtils::Number2String(uint32_t number) {
    return QString::number(number);
}

QString StringUtils::Dec2Number2HexString(uint32_t numberDec) {
    return QString(QSTRING_PARAM_FIRST).arg(numberDec, STRING_FILL_NUM_ZERO_VAL, RADIX_HEX);
}

QString StringUtils::Dec2Number2FilledHexString(uint32_t numberDec, uint32_t fillWidth) {
    return QString(QSTRING_PARAM_FIRST).arg(numberDec, fillWidth, RADIX_HEX, QLatin1Char(STRING_FILL_STR_ZERO_VAL));
}
