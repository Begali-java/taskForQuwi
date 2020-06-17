#ifndef COREAPIFUNCTIONS_H
#define COREAPIFUNCTIONS_H

#include <QObject>
#include <QString>
#include <QSettings>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QUrl>
#include <QByteArray>
#include <QSettings>
#include <QVector>
#include <QDebug>

/*CORE STATIC VARIABLES*/
#include "core/core_static_variable_definations.h"
#include "core/core_structure_definations.h"

class CoreApiFunctions : public QObject
{
    Q_OBJECT
public:
    explicit CoreApiFunctions(QObject *parent = nullptr);
private:
    QNetworkAccessManager * manager = 0;
public slots:
    void setNetworkManagerCommand(QNetworkRequest request,QByteArray postData);
    void setNetworkManagerCommandGet(QNetworkRequest request);
    void setNetworkManagerCommandPostUpdate(QNetworkRequest request,QByteArray postData);
    void onFinished(QNetworkReply *reply);
    void parseRequest(QString url,QString jsonStr);
    void setProjectListChangedSignal(QVector<structure_definations::core::ProjectsList> listOfProjects);
    QJsonObject getJsonObjectFromString(QString jsonStr);
    void setProjectDeatilOpened(structure_definations::core::ProjectsList projectItem);

signals:
    void setErrorStatusWithMsgStr(bool,QString msgStr);
    void projectListChangedSignal(QVector<structure_definations::core::ProjectsList> listOfProjects);
    void projectDeatilOpenedSignal(structure_definations::core::ProjectsList projectItem);

};

#endif // COREAPIFUNCTIONS_H
