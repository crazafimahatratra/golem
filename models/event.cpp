#include "event.h"
#include <QDebug>
Event::Event():QSqliteWrapper::Table("event")
{

}

QList<QDate> Event::allDateEvents()
{
    Event *model = new Event();
    QList<QDate> res;
    model->select("DISTINCT strftime('%Y-%m-%d', evedate) as d");
    model->order("evedate DESC");
    QList<QSqlRecord> records = model->exec();
    for(int i = 0; i < records.length(); i++)
    {
        res.append(QDate::fromString(records[i].value("d").toString(), "yyyy-MM-dd"));
    }
    delete model;
    return res;
}
