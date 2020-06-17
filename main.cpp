#include "containerwindow.h"
#include"projecteditwindow.h"

#include <QApplication>
#include <QFile>
#include <QString>
/*CORE FUNCTIONS*/
#include "core/core_api_application.h"
#include "core/core_structure_definations.h"

int main(int argc, char *argv[])
{
    core::qt::quwi::Application aApp(argc, argv);
    qRegisterMetaType< structure_definations::core::ProjectsList >();
    qRegisterMetaType< structure_definations::core::UsersList >();
    ContainerWindow w;
    w.initAllSettings();
    w.setLoginWindow();
    w.show();

  //  ProjectEditWindow pw;
  //  pw.show();

    QFile File(":/style.qss");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());
    qApp->setStyleSheet(StyleSheet);
    return aApp.exec();
}
