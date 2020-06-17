#ifndef UISETTINGS_H
#define UISETTINGS_H

#include <QObject>
#include <QSettings>
#include <QString>

#include <QDebug>

class UISettings : public QObject
{
    Q_OBJECT
public:
    explicit UISettings(QObject *parent = nullptr);
public:
    QString getLastEmail();
    QString getToken();
signals:

};

#endif // UISETTINGS_H
