#ifndef CORE_STRUCTURE_DEFINATIONS_H
#define CORE_STRUCTURE_DEFINATIONS_H
#include <QString>
#include <QByteArray>
#include <QMetaType>
#include <QVector>
namespace structure_definations { namespace core {

typedef struct {
    qint64 id;
    QString name;
    QString avatar_url;
    QString dta_activity;
    qint64 is_online;

} UsersList;

typedef struct
{
    QString projectName;
    int activeStatus;
    QString logoUrl;
    QByteArray imageArray;
    qint64 id;
    qint64 is_owner_watcher;
    qint64 spent_time_week;
    qint64 spent_time_month;
    qint64 spent_time_all;
    QVector<UsersList> usersList;

} ProjectsList;

}}
Q_DECLARE_METATYPE(structure_definations::core::ProjectsList);
Q_DECLARE_METATYPE(structure_definations::core::UsersList);
#endif // CORE_STRUCTURE_DEFINATIONS_H
