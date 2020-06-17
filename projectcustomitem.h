#ifndef PROJECTCUSTOMITEM_H
#define PROJECTCUSTOMITEM_H

#include <QWidget>
#include <QString>
#include <QImage>
#include <QPixmap>
#include <QDateTime>
#include <QDate>
#include <QMouseEvent>
#include <QDebug>

/*CORE FUNCTIONS*/
#include "core/core_structure_definations.h"
#include "core/filedownloader.h"
#include "core/core_api_application.h"

namespace Ui {
class ProjectCustomItem;
}

class ProjectCustomItem : public QWidget
{
    Q_OBJECT

public:
    explicit ProjectCustomItem(QWidget *parent = nullptr);
    ~ProjectCustomItem();
private:
    structure_definations::core::ProjectsList m_projectItem;
    FileDownloader *m_downloader = 0;
public slots:
    void initAllSettings();
    void setProjectitem(structure_definations::core::ProjectsList projectItem);
    void loadUrlImage();
private:
    Ui::ProjectCustomItem *ui;
protected:
    void mousePressEvent(QMouseEvent *event);
};

#endif // PROJECTCUSTOMITEM_H
