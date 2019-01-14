#include "task.h"
#include "constants.h"

Task::Task():QSqliteWrapper::Table("task")
{

}

Task::timelineCategory Task::getTimelineCategory()
{
    if(this->dueDate.date() == QDate::currentDate())
        return Today;
    if(this->dueDate.date() < QDate::currentDate())
        return Overdue;
    return UpNext;
}

QMap<int, int> Task::countByProject()
{
    Task *model = new Task();
    QMap<int, int> result;
    model->select("count(*) as c")->select("project_id");
    model->where("status !=", TASK_STATUS_FINISHED);
    model->groupBy("project_id");
    QList<QSqlRecord> records = model->exec();
    for(int i = 0; i < records.length(); i++)
    {
        result[records[i].value("project_id").toInt()] = records[i].value("c").toInt();
    }
    delete model;
    return result;
}
