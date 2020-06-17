#ifndef CONTAINERWINDOW_H
#define CONTAINERWINDOW_H

#include <QWidget>
#include <QString>
#include <QMessageBox>
#include <QDebug>
/*INCLUDE ALL WIDGETS*/
#include "loginwindow.h"
#include "projectlistwindow.h"
#include "projecteditwindow.h"
/*core functions*/
#include "core/core_static_variable_definations.h"
#include "core/core_api_application.h"
#include "core/core_structure_definations.h"\

QT_BEGIN_NAMESPACE
namespace Ui { class ContainerWindow; }
QT_END_NAMESPACE

class ContainerWindow : public QWidget
{
    Q_OBJECT

public:
    ContainerWindow(QWidget *parent = nullptr);
    ~ContainerWindow();
public slots:
    /*INIT ALL SETTINGS*/
    void initAllSettings();
    /*LOGIN WINDOW*/
    void setLoginWindow();
    /*PROJECT WINDOW*/
    void setProjectWindow();
    /*PROJECT EDIT WINDOW*/
    void setProjectEditWindow();
    /*GLOBAL FUNCTIONS*/
    void setShowErrorMessage(int status,QString msgStr);
    void setProjectItemClicedFunction(structure_definations::core::ProjectsList projectItem);

private:
    Ui::ContainerWindow *ui;
    LoginWindow *m_login = 0;
    ProjectListWindow *m_projectList = 0;
    ProjectEditWindow *m_projectEdit = 0;

};
#endif // CONTAINERWINDOW_H
