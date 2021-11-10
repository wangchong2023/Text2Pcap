#include "buildutils.h"
#include "Common/common_header.h"

BuildUtils::BuildUtils(QObject *parent) : QObject(parent)
{

}

QDateTime BuildUtils::buildDateTime()
{
    QString dateTimeString;
    dateTimeString += __DATE__;
    dateTimeString += __TIME__;

    /* " "是两个空格，用于日期为单数时需要转成“空格+0” */
    dateTimeString.replace("  "," 0");

    QDateTime dateTime = QLocale(QLocale::English).toDateTime(dateTimeString, "MMM dd yyyyhh:mm:ss");

    return dateTime;
}

QString BuildUtils::getBuildDateTime()
{
    QDateTime datetime = buildDateTime();
    return datetime.toLocalTime().toString("yyyy-MM-dd hh:mm:ss");
}
