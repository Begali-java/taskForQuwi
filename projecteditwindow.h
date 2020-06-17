#ifndef PROJECTEDITWINDOW_H
#define PROJECTEDITWINDOW_H

#include <QWidget>
#include <QString>
#include <QVector>
#include <QDebug>
#include <QMessageBox>

/*CORE FUNCTIONS*/
#include "core/core_api_application.h"
#include "core/core_structure_definations.h"

namespace Ui {
class ProjectEditWindow;
}

class ProjectEditWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ProjectEditWindow(QWidget *parent = nullptr);
    ~ProjectEditWindow();
public slots:
    void initAllSettings(structure_definations::core::ProjectsList projectItem);
private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_4_clicked();

private:
    Ui::ProjectEditWindow *ui;
    structure_definations::core::ProjectsList m_projectItem;

signals:
    void openProjectListWindow();

};

#endif // PROJECTEDITWINDOW_H
