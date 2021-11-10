#ifndef BUILDUTILS_H
#define BUILDUTILS_H

#include <QObject>

class BuildUtils : public QObject
{
    Q_OBJECT
public:
    explicit BuildUtils(QObject *parent = nullptr);
    static QDateTime buildDateTime();
    static QString getBuildDateTime();

signals:

};

#endif // BUILDUTILS_H
