#ifndef EVENT_H
#define EVENT_H
#include "qtkit/QSqliteWrapper/table.h"
#include <QDateTime>

class Event: public QSqliteWrapper::Table
{
public:
    Event();

    // Table interface
public:
    QString pkName()
    {
        return "id";
    }
    QVariant pkValue()
    {
        return this->id;
    }
    void setPkValue(QVariant value)
    {
        this->id = value.toInt();
    }
    void fromRecord(QSqlRecord record)
    {
        this->id = record.value("id").toInt();
        this->project_id = record.value("project_id").toInt();
        this->title = record.value("title").toString();
        this->evedate = record.value("evedate").toDateTime();
        this->content = record.value("content").toString();
    }
    QList<QSqliteWrapper::Parameter> prepareParameters()
    {
        QList<QSqliteWrapper::Parameter> parameters;
        parameters.append(QSqliteWrapper::Parameter("project_id", this->project_id));
        parameters.append(QSqliteWrapper::Parameter("title", this->title));
        parameters.append(QSqliteWrapper::Parameter("evedate", this->evedate));
        parameters.append(QSqliteWrapper::Parameter("content", this->content));
    }

    int id;
    int project_id;
    QString title;
    QDateTime evedate;
    QString content;
};

#endif // EVENT_H
