#include "core_api_application.h"
using namespace core::qt::quwi;


Application::Application(int& a_argc, char** a_argv)
    :
      ::QApplication (a_argc,a_argv)
{

  connect(&m_apifunctions,SIGNAL(setErrorStatusWithMsgStr(bool, QString)),this,SLOT(setLoginStatus(bool,QString)));
  connect(&m_apifunctions,SIGNAL(projectListChangedSignal(QVector<structure_definations::core::ProjectsList>)),this,SIGNAL(projectListSignal(QVector<structure_definations::core::ProjectsList>)));
}

Application::~Application()
{
    ::QCoreApplication::processEvents();
}

void Application::loginGuiThreadOnly(QString login, QString password)
{
    if(login.trimmed().length() >0 && password.trimmed().length() && password.trimmed().length() >0){
        /*CHECK LOGIN FROM API*/
        QNetworkRequest request(QUrl(statics_definations::core::BASE_URL+"auth/login"));
        request.setRawHeader("Content-Type", "application/json");
        request.setRawHeader("Client-Timezone-Offset", "60");
        request.setRawHeader("Client-Language", "ru-RU");
        request.setRawHeader("Client-Company", "udimi");
        request.setRawHeader("Client-Device", "desktop");
        QJsonObject obj;
        obj["email"] = login;
        obj["password"] = password;

        m_apifunctions.setNetworkManagerCommand(request,QJsonDocument(obj).toJson());

    }else{
        emit loginErorSignal(statics_definations::core::ERROR_LOGIN_LOGIN_AND_PASSWORD_NOT_BE_EMPITY,tr("Empity login or password"));
    }

}
void Application::getProjectList(){
    QNetworkRequest request(QUrl(statics_definations::core::BASE_URL+"projects-manage"));
    request.setRawHeader("Content-Type", "application/json");
    QString tokenUrl = "Bearer "+getToken();
    request.setRawHeader("Authorization", tokenUrl.toUtf8());
    m_apifunctions.setNetworkManagerCommandGet(request);


}

void Application::updateProjectName(QString name, double projectId)
{
    QNetworkRequest request(QUrl(statics_definations::core::BASE_URL+"projects-manage/update?id="+QString::number(projectId)));
    request.setRawHeader("Content-Type", "application/x-www-form-urlencoded");
    QString tokenUrl = "Bearer "+getToken();
    request.setRawHeader("Authorization", tokenUrl.toUtf8());
    QByteArray postBody;
    postBody.append("name="+name);
    m_apifunctions.setNetworkManagerCommand(request,postBody);
}
QString Application::getLastEmail()
{
    return m_settingsClass.getLastEmail();
}

void Application::setLoginStatus(bool m_status, QString msgStr)
{
    if(m_status){
        emit loginSuccessSignal();
    }else{
        emit loginErorSignal(statics_definations::core::LOGIN_ERROR_WITH_AUTH,msgStr);
    }
}

void Application::showMessageGuiThreadOnly(int msgStatus, QString msgStr)
{
    emit showMessageSiganl(msgStatus,msgStr);
}

QString Application::getToken()
{
    return m_settingsClass.getToken();
}

void Application::setProjectDeatilOpened(structure_definations::core::ProjectsList projectItem)
{
    emit projectDeatilOpenedSignal(projectItem);
}


