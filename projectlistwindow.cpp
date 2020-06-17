#include "projectlistwindow.h"
#include "ui_projectlistwindow.h"

ProjectListWindow::ProjectListWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProjectListWindow)
{
    ui->setupUi(this);
    connect(thisApp(),SIGNAL(projectListSignal(QVector<structure_definations::core::ProjectsList>)),this,SLOT(loadProjectlist(QVector<structure_definations::core::ProjectsList>)));
}

ProjectListWindow::~ProjectListWindow()
{
    delete ui;
}

void ProjectListWindow::loadProjectlist(QVector<structure_definations::core::ProjectsList> projectList)
{
    foreach(QListWidgetItem* item, ui->listWidget->findItems("*", Qt::MatchWildcard)){
        QWidget *widget = ui->listWidget->itemWidget(item);
        delete widget;
        delete item;
    }
    /**/
    for(int i  = 0; i < projectList.size(); i++){
        /*INIT CUSTOM ITEM*/
        /*BEGIN*/
        QListWidgetItem *m_item = new QListWidgetItem;
        ProjectCustomItem *m_custom_list_item = new ProjectCustomItem;
        m_custom_list_item->setProjectitem(projectList.at(i));
        m_custom_list_item->initAllSettings();
        m_item->setSizeHint(m_custom_list_item->size());
        ui->listWidget->insertItem(i,m_item);
        ui->listWidget->setItemWidget(m_item,m_custom_list_item);
        /*END*/
        QCoreApplication::processEvents();
    }

}

void ProjectListWindow::on_projectsBtn_clicked()
{

}

void ProjectListWindow::on_logoutButton_clicked()
{
  //thisApp()->updateProjectName("TEST BEHZOD",864);
}
