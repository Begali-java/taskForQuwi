#ifndef CORE_API_APPLICATION_H
#define CORE_API_APPLICATION_H
#include <QObject>
#include <QApplication>
#include <QString>
#include <QSettings>
#include <QDebug>

#include "core_static_variable_definations.h"
#include "core/uisettings.h"
#include "core/core_api_functions.h"


#define thisApp()  static_cast< ::core::qt::quwi::Application* >( ::QCoreApplication::instance() )
namespace core { namespace qt { namespace quwi {
class Application final : public ::QApplication
{

    Q_OBJECT

public:
    Application(int& argc, char** argv);
    ~Application() override;
private:
    UISettings m_settingsClass;
    CoreApiFunctions m_apifunctions;

public slots:
    /*LOGIN FUNCTIONS*/
    void loginGuiThreadOnly(QString login, QString password);
    QString getLastEmail();
    void setLoginStatus(bool m_status,QString msgStr);
    /*PROJECT LIST*/
    void getProjectList();
    void updateProjectName(QString name, double projectId);

    /*GLOBAL FUNCTIONS*/
    void showMessageGuiThreadOnly(int msgStatus,QString msgStr);
    QString getToken();
    void setProjectDeatilOpened(structure_definations::core::ProjectsList projectItem);


signals:
    void loginErorSignal(int errorStatsu, QString errorString );
    void loginSuccessSignal();
    void showMessageSiganl(int msgStatus,QString msgStr);
    void projectListSignal(QVector<structure_definations::core::ProjectsList> listOfProjects);
    void projectDeatilOpenedSignal(structure_definations::core::ProjectsList projectItem);

};

}}}

#endif // CORE_API_APPLICATION_H
