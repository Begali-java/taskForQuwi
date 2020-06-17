#include "projectcustomitem.h"
#include "ui_projectcustomitem.h"

ProjectCustomItem::ProjectCustomItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProjectCustomItem)
{
    ui->setupUi(this);
}

ProjectCustomItem::~ProjectCustomItem()
{
    delete ui;
}

void ProjectCustomItem::initAllSettings()
{
    ui->projectName->setText(m_projectItem.projectName);
    if(m_projectItem.activeStatus == 1){
        ui->statuslabel->setText("<b style='color:green;'>Avtive</b>");
    }else{
        ui->statuslabel->setText("<b style='color:grey;'>Inactive</b>");
    }

    QString thisWeekStr = QDateTime::fromTime_t(m_projectItem.spent_time_week).toUTC().toString("hh:mm:ss");
    QString thisMonthStr = QDateTime::fromTime_t(m_projectItem.spent_time_month).toUTC().toString("hh:mm:ss");
    QString thisTotalStr = QDateTime::fromTime_t(m_projectItem.spent_time_all).toUTC().toString("hh:mm:ss");
    ui->weekLabelValue->setText(thisWeekStr);
    ui->monthLabelValue->setText(thisMonthStr);
    ui->totalLabelValue->setText(thisTotalStr);

    if(m_projectItem.logoUrl.trimmed().length() == 0){
        return;
    }
    /*LOAD IMAGE FROM URL*/
    QUrl logoImageUrl(m_projectItem.logoUrl);
    m_downloader = new FileDownloader(logoImageUrl, this);
    connect(m_downloader, SIGNAL (downloaded()), this, SLOT (loadUrlImage()));

}

void ProjectCustomItem::setProjectitem(structure_definations::core::ProjectsList projectItem)
{
    m_projectItem = projectItem;
}

void ProjectCustomItem::loadUrlImage()
{
    QPixmap logoImage;
    logoImage.loadFromData(m_downloader->downloadedData());
    ui->imglabel->setPixmap(logoImage);
    ui->imglabel->setScaledContents(true);
}

void ProjectCustomItem::mousePressEvent(QMouseEvent *event){
    Q_UNUSED(event)
    thisApp()->setProjectDeatilOpened(m_projectItem);
}
