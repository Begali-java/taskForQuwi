#ifndef PROJECTLISTWINDOW_H
#define PROJECTLISTWINDOW_H

#include <QWidget>
#include <QString>
#include <QSettings>
#include <QVector>
#include <QListWidget>
#include <QListWidgetItem>
#include <QDebug>

/*CORE FUNCTIONS*/
#include "core/core_api_application.h"
#include "core/core_structure_definations.h"

/*CUSTOM ITEM*/
#include "projectcustomitem.h"

namespace Ui {
class ProjectListWindow;
}

class ProjectListWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ProjectListWindow(QWidget *parent = nullptr);
    ~ProjectListWindow();
public slots:
    void loadProjectlist(QVector<structure_definations::core::ProjectsList> projectList);

private slots:
    void on_projectsBtn_clicked();
    void on_logoutButton_clicked();

private:
    Ui::ProjectListWindow *ui;
};

#endif // PROJECTLISTWINDOW_H
