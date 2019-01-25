#include "notificationelement.h"
#include "ui_notificationelement.h"
#include "constants.h"

NotificationElement::NotificationElement(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NotificationElement)
{
    ui->setupUi(this);
    m_taskid = 0;
    ui->labelTitle->setTextFormat(Qt::RichText);
    ui->labelProjectName->setTextFormat(Qt::RichText);
    ui->labelText->setTextFormat(Qt::RichText);
}

NotificationElement::~NotificationElement()
{
    delete ui;
}

void NotificationElement::setTask(Task *task)
{
    QString color="black";
    Task::timelineCategory category = task->getTimelineCategory();
    if(category == Task::Overdue)
    {
        color = "red";
    }
    ui->labelTitle->setText(QString("<font color='%2'>%1</font>").arg(task->title).arg(color));
    ui->labelText->setText(QString("<font color='%2'>%1</font>").arg(task->dueDate.toString(DATETIME_FORMAT)).arg(color));
    if(task->priority == Task::Important)
    {
        ui->labelIcon->setPixmap(QPixmap(":/png/icons/exclamation-red.png"));
    }
    else if(task->priority == Task::LessImportant)
    {
        ui->labelIcon->setPixmap(QPixmap(":/png/icons/exclamation-white.png"));
    }
    else if(task->priority == Task::Normal)
    {
        ui->labelIcon->setPixmap(QPixmap(":/png/icons/16x16-empty.png"));
    }
    Project *p = Project::findById<Project>(task->project_id);
    if(p)
    {
        ui->labelProjectName->setText(QString("<font color='%2'>%1</font>").arg(p->name).arg(color));
        delete p;
    }
    else
    {
        ui->labelProjectName->setText("[UNKOWN]");
    }

    m_taskid = task->id;
}

int NotificationElement::taskId()
{
    return m_taskid;
}

void NotificationElement::on_pushButtonDone_clicked()
{
    emit this->taskDone(m_taskid);
}

void NotificationElement::on_pushButtonGo_clicked()
{
    emit this->taskDetailsRequested(m_taskid);
}
