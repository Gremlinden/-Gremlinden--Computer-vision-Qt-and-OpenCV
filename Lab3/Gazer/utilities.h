#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <QString>
#include <QObject>
#include <QApplication>
#include <QDateTime>
#include <QDir>
#include <QStandardPaths>

class Utilities
{
 public:
    static QString getDataPath();
    static QString newSavedVideoName();
    static QString getSavedVideoPath(QString name, QString postfix);
};

#endif
