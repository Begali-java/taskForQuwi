#include "projecteditwindow.h"
#include "ui_projecteditwindow.h"

ProjectEditWindow::ProjectEditWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProjectEditWindow)
{
    ui->setupUi(this);
}

ProjectEditWindow::~ProjectEditWindow()
{
    delete ui;
}

void ProjectEditWindow::initAllSettings(structure_definations::core::ProjectsList projectItem){
    Q_UNUSED(projectItem)
    m_projectItem = projectItem;
    ui->lineEdit->setText(m_projectItem.projectName);
    if(m_projectItem.activeStatus == 1){
        ui->pushButton->setText("Active");
    }else{
        ui->pushButton->setText("Inactive");
    }

    if(m_projectItem.is_owner_watcher == 1){
        ui->pushButton_3->setText("Active");
    }else{
        ui->pushButton_3->setText("Inactive");
    }

    QVector<structure_definations::core::UsersList> usersList = m_projectItem.usersList;
    ui->listWidget->clear();
    for(int i = 0; i < usersList.size(); i ++){
        ui->listWidget->addItem(usersList.at(i).name);
    }

}

void ProjectEditWindow::on_pushButton_2_clicked()
{
    QString projectNameStr = ui->lineEdit->text().trimmed();
    if(projectNameStr.length()){

        thisApp()->updateProjectName(projectNameStr,m_projectItem.id);
        QMessageBox msgBox;
        msgBox.information(this, tr("Success"), tr("project name is updated"));

    }else{
        qDebug()<<"ERROR FILL ALL FIELDS";
        QMessageBox msgBox;
        msgBox.critical(this, tr("ERROR"), tr("project name is empity"));
    }
}

void ProjectEditWindow::on_pushButton_4_clicked()
{
    emit openProjectListWindow();
}
