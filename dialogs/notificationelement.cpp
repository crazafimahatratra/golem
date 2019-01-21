#include "notificationelement.h"
#include "ui_notificationelement.h"
#include "constants.h"

NotificationElement::NotificationElement(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NotificationElement)
{
    ui->setupUi(this);
    m_taskid = 0;
}

NotificationElement::~NotificationElement()
{
    delete ui;
}

void NotificationElement::setTask(Task *task)
{
    ui->labelTitle->setText(task->title);
    ui->labelText->setText(task->dueDate.toString(DATETIME_FORMAT));
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
        ui->labelProjectName->setText(p->name);
        delete p;
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
