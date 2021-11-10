#ifndef FONTUTILS_H
#define FONTUTILS_H

#include <QObject>
#include <QFont>

class FontUtils : public QObject
{
    Q_OBJECT
public:
    explicit FontUtils(QObject *parent = nullptr);

signals:
public:
    static void SetAppFont(QString family, int pixelSize);
    static void SetDefaultAppFont();
    static void SetToolTipFont(QString family, int pixelSize);
    static void SetDefaultToolTipFont();
};

#endif // FONTUTILS_H
