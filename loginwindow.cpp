#include "loginwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::initAllSettings(){

    ui->passwordLineEdit->setText("");
    ui->emailLineEdit->setText(thisApp()->getLastEmail());

    /*FOR TEST*/
    //ui->emailLineEdit->setText("vitaliibondtest@gmail.com");
  //  ui->passwordLineEdit->setText("vitaliibondtest");

}

void LoginWindow::setLastSuccesEmail()
{
    QSettings m_settings("config.ini",QSettings::IniFormat);
    m_settings.beginGroup("SETTINGS");
    m_settings.setValue("email",ui->emailLineEdit->text().trimmed());
    m_settings.endGroup();
    ui->passwordLineEdit->setText("");
}

void LoginWindow::on_loginPushbutton_clicked()
{
     if(ui->emailLineEdit->text().trimmed().length() > 0  && ui->passwordLineEdit->text().trimmed().length() > 0){
         thisApp()->loginGuiThreadOnly(ui->emailLineEdit->text().trimmed(),ui->passwordLineEdit->text());
     }else{
         thisApp()->setLoginStatus(false,tr("Empity login or password"));
     }
}
