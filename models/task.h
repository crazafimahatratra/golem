#ifndef TASK_H
#define TASK_H
#include "qtkit/QSqliteWrapper/table.h"
#include <QDateTime>

/**
 * @brief Represents the table task in database
 */
class Task: public QSqliteWrapper::Table
{
public:
    Task();

    // Table interface
public:
    /**
     * @brief Category of a task regarding its due date
     */
    enum timelineCategory {
        Overdue = 0,    ///< The task is overdue
        Today = 1,      ///< The task is for today
        UpNext = 2      ///< The task is for tomorrow or even later.
    };

    /**
     * @brief Priorities of tasks
     */
    enum taskPriority {
        LessImportant   = -1,   ///< Less important
        Normal          = 0,    ///< Priority normal
        Important       = 1,    ///< An important task
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
        this->priority = record.value("priority").toInt();
        this->project_name = record.value("project_name").toString();
    }
    QList<QSqliteWrapper::Parameter> prepareParameters()
    {
        QList<QSqliteWrapper::Parameter> parameters;
        parameters.append(QSqliteWrapper::Parameter("project_id", this->project_id));
        parameters.append(QSqliteWrapper::Parameter("title", this->title));
        parameters.append(QSqliteWrapper::Parameter("content", this->content));
        parameters.append(QSqliteWrapper::Parameter("duedate", this->dueDate));
        parameters.append(QSqliteWrapper::Parameter("status", this->status));
        parameters.append(QSqliteWrapper::Parameter("priority", this->priority));
        return parameters;
    }

    /**
     * @brief Checks if a task is a today's task or an overdue or an upcoming task.
     * @return
     */
    timelineCategory getTimelineCategory();

    /**
     * @brief Count tasks by project `(SELECT count(*), project_id FROM project)`
     * @return a map containing id_project and the number of tasks inside.
     */
    static QMap<int, int> countByProject();

    /**
     * @brief id of the task
     */
    int id;

    /**
     * @brief id of the project containing the task
     * @see Project::id
     */
    int project_id;

    /**
     * @brief Title of the task
     */
    QString title;

    /**
     * @brief Content of the task (comment)
     */
    QString content;

    /**
     * @brief Task due date
     */
    QDateTime dueDate;

    /**
     * @brief Task status
     * @see constants.h
     */
    int status;

    /**
     * @brief Task priority
     */
    int priority;

    /**
     * @brief Name of the project
     * @see Project::name
     */
    QString project_name;
};

#endif // TASK_H
