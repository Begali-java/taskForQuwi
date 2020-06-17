#include "core_api_functions.h"

CoreApiFunctions::CoreApiFunctions(QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(onFinished(QNetworkReply *)));
}

void CoreApiFunctions::setNetworkManagerCommand(QNetworkRequest request, QByteArray postData)
{
    if(manager != 0){
        QNetworkReply *replySending = manager->post(request,postData);
        if(replySending->error() != QNetworkReply::NoError){
            /*ERROR*/
            qDebug()<<"ERROR";
            emit setErrorStatusWithMsgStr(false,tr("SERVER ERROR"));
        }
    }
}

void CoreApiFunctions::setNetworkManagerCommandGet(QNetworkRequest request){
    if(manager != 0){
        QNetworkReply *replySending = manager->get(request);
        if(replySending->error() != QNetworkReply::NoError){
            /*ERROR*/
            qDebug()<<"ERROR";
            emit setErrorStatusWithMsgStr(false,tr("SERVER ERROR"));
        }
    }
}

void CoreApiFunctions::setNetworkManagerCommandPostUpdate(QNetworkRequest request, QByteArray postData)
{
    if(manager != 0){
        QNetworkReply *replySending = manager->post(request,postData);
        if(replySending->error() != QNetworkReply::NoError){
            /*ERROR*/
            qDebug()<<"ERROR";
            emit setErrorStatusWithMsgStr(false,tr("SERVER ERROR"));
        }
    }
}

void CoreApiFunctions::onFinished(QNetworkReply *reply)
{
    QString strReply = (QString)reply->readAll();
    parseRequest(reply->url().toString(),strReply);
    Q_UNUSED(reply)
}

void CoreApiFunctions::parseRequest(QString url, QString jsonStr)
{
    if(url.trimmed().length() > 0){
        url = url.remove(statics_definations::core::BASE_URL,Qt::CaseInsensitive);
        url = url.toLower();
        if(QString::compare(url,"auth/login",Qt::CaseInsensitive) == 0){
            QJsonObject jsonObj = getJsonObjectFromString(jsonStr);
            if(!jsonObj.isEmpty()){
                if(jsonObj.contains("token")){
                    QString m_token = jsonObj["token"].toString();
                    QSettings m_settings("config.ini",QSettings::IniFormat);
                    m_settings.beginGroup("SETTINGS");
                    m_settings.setValue("token",m_token);
                    m_settings.endGroup();
                    qDebug()<<"LOGIN SUCCESS";
                    emit setErrorStatusWithMsgStr(true,tr("SUCCESS"));
                }else if(jsonObj.contains("first_errors")){
                    QJsonObject subJsonObj = jsonObj["first_errors"].toObject();
                    if(subJsonObj.isEmpty()){
                        emit setErrorStatusWithMsgStr(false,tr("ERROR"));
                        return;
                    }

                    QStringList m_keys =subJsonObj.keys();
                    QString errorMsg = "";
                    for(int i = 0; i < m_keys.length(); i++){
                        errorMsg.append(subJsonObj[m_keys.at(i)].toString());
                    }
                    emit setErrorStatusWithMsgStr(false,errorMsg);
                }
            }
        }else if(QString::compare(url,"projects-manage",Qt::CaseInsensitive) == 0){
            /*PROJECT LIST*/
            QJsonObject objProject = getJsonObjectFromString(jsonStr);
            if(objProject.contains("projects")){
                QJsonArray projectsArray = objProject["projects"].toArray();
                QVector<structure_definations::core::ProjectsList> listOfProjects;

                for(int a = 0; a < projectsArray.size(); a++){

                  QJsonObject valueofProject = projectsArray.at(a).toObject();

                  /*ITEM*/
                  structure_definations::core::ProjectsList projectItem;
                  projectItem.id = valueofProject["id"].toDouble();
                  projectItem.logoUrl = valueofProject["logo_url"].toString();
                  projectItem.projectName = valueofProject["name"].toString();
                  projectItem.activeStatus = valueofProject["is_active"].toInt();
                  projectItem.spent_time_week = valueofProject["spent_time_week"].toDouble();
                  projectItem.spent_time_month = valueofProject["spent_time_month"].toDouble();
                  projectItem.spent_time_all = valueofProject["spent_time_all"].toDouble();
                  projectItem.is_owner_watcher = valueofProject["is_owner_watcher"].toDouble();

                  QVector<structure_definations::core::UsersList> usersListStr;

                  QJsonArray arrayUsers = valueofProject["users"].toArray();
                  for(int k = 0; k < arrayUsers.size(); k++){
                      QJsonObject objUserItem = arrayUsers.at(k).toObject();
                      structure_definations::core::UsersList userItem;
                      userItem.id = objUserItem["id"].toInt();
                      userItem.name = objUserItem["name"].toString();
                      userItem.avatar_url = objUserItem["avatar_url"].toString();
                      userItem.dta_activity = objUserItem["dta_activity"].toString();
                      usersListStr.append(userItem);

                  }
                  projectItem.usersList = usersListStr;
                  listOfProjects.append(projectItem);

                }

                /*EMIT PROJECT CHANGED SIGNAL*/
                emit projectListChangedSignal(listOfProjects);
            }

        }else{
            qDebug()<<jsonStr;
        }
    }
}

void CoreApiFunctions::setProjectListChangedSignal(QVector<structure_definations::core::ProjectsList> listOfProjects)
{
    emit  projectListChangedSignal(listOfProjects);
}

QJsonObject CoreApiFunctions::getJsonObjectFromString(QString jsonStr)
{
    QJsonObject obj;
    QJsonDocument doc = QJsonDocument::fromJson(jsonStr.toUtf8());
    if(!doc.isNull()){
        if(doc.isObject()){
            obj = doc.object();
        }
        else{
            qDebug() << "NOT OBJECT FOUND ERROR" << endl;
        }
    }
    else{
        qDebug() <<"INVALID JSON ERROR";
    }
    return obj;
}

void CoreApiFunctions::setProjectDeatilOpened(structure_definations::core::ProjectsList projectItem){
    emit projectDeatilOpenedSignal(projectItem);
}
