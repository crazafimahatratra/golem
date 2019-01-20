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
