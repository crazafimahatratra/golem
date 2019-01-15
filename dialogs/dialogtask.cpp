#include "dialogtask.h"
#include "ui_dialogtask.h"
#include "constants.h"

DialogTask::DialogTask(int project_id, int task_id, MainWindow *parent) :
    QDialog(parent),
    ui(new Ui::DialogTask),
    m_parent(parent)
{
    ui->setupUi(this);

    m_task = Task::findById<Task>(task_id);
    if(!m_task)
    {
        m_task = new Task();
        m_task->id = 0;
        m_task->status = TASK_STATUS_STARTED;
    }
    else
    {
        project_id = m_task->project_id;
    }

    Project *model = new Project();
    QList<Project *> rows = model->order("name")->get<Project>();
    delete model;
    for(int i = 0; i < rows.length(); i++)
    {
        ui->comboBoxProject->addItem(rows[i]->name, rows[i]->id);
        if(rows[i]->id == project_id)
            ui->comboBoxProject->setCurrentIndex(i);
        delete rows[i];
    }
    ui->lineEditTitle->setFocus();

    ui->dateTimeEditDueDate->setDateTime(QDateTime::currentDateTime());
    ui->lineEditTitle->setText(m_task->title);
    ui->textEditContent->setHtml(m_task->content);
    ui->dateTimeEditDueDate->setDateTime(m_task->dueDate);
}

DialogTask::~DialogTask()
{
    delete ui;
    if(m_task)
        delete m_task;
}

void DialogTask::on_pushButtonCancel_clicked()
{
    this->reject();
}

void DialogTask::on_pushButtonOK_clicked()
{
    int old_project_id = m_task->project_id;
    m_task->project_id = ui->comboBoxProject->currentData(Qt::UserRole).toInt();
    m_task->title = ui->lineEditTitle->text();
    m_task->dueDate = ui->dateTimeEditDueDate->dateTime();
    m_task->content = ui->textEditContent->toHtml();
    if(m_task->id)
    {
        m_task->update();
        emit m_parent->taskUpdated(m_task->id, m_task->project_id, old_project_id);
    }
    else
    {
        m_task->insert();
        emit m_parent->taskUpdated(m_task->id, m_task->project_id, m_task->project_id);
    }
    this->accept();
}
