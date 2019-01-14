#ifndef TASK_H
#define TASK_H
#include "qtkit/QSqliteWrapper/table.h"
#include <QDateTime>

class Task: public QSqliteWrapper::Table
{
public:
    Task();

    // Table interface
public:
    enum timelineCategory {
        Overdue = 0,
        Today = 1,
        UpNext = 2
    };
    QString pkName() { return "id"; }
    QVariant pkValue() { return this->id; }
    void setPkValue(QVariant value) { this->id = value.toInt(); }
    void fromRecord(QSqlRecord record)
    {
        this->id = record.value("id").toInt();
        this->project_id = record.value("project_id").toInt();
        this->title = record.value("title").toString();
        this->content = record.value("content").toString();
        this->dueDate = record.value("duedate").toDateTime();
        this->status = record.value("status").toInt();
    }
    QList<QSqliteWrapper::Parameter> prepareParameters()
    {
        QList<QSqliteWrapper::Parameter> parameters;
        parameters.append(QSqliteWrapper::Parameter("project_id", this->project_id));
        parameters.append(QSqliteWrapper::Parameter("title", this->title));
        parameters.append(QSqliteWrapper::Parameter("content", this->content));
        parameters.append(QSqliteWrapper::Parameter("duedate", this->dueDate));
        parameters.append(QSqliteWrapper::Parameter("status", this->status));
        return parameters;
    }

    timelineCategory getTimelineCategory();
    static QMap<int, int> countByProject();

    int id;
    int project_id;
    QString title;
    QString content;
    QDateTime dueDate;
    int status;
};

#endif // TASK_H
