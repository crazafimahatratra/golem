#include "dialogtask.h"
#include "ui_dialogtask.h"
#include "constants.h"
#include "bus.h"

DialogTask::DialogTask(int project_id, int task_id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogTask)
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
    ui->widgetRtfContent->setHtml(m_task->content);
    ui->dateTimeEditDueDate->setDateTime(m_task->dueDate);

    // task priorities
    ui->comboBoxPriority->addItem("Less important", Task::LessImportant);
    ui->comboBoxPriority->addItem("Normal", Task::Normal);
    ui->comboBoxPriority->addItem("Important", Task::Important);
    for(int i = 0; i < ui->comboBoxPriority->count(); i++)
    {
        if(ui->comboBoxPriority->itemData(i).toInt() == m_task->priority)
        {
            ui->comboBoxPriority->setCurrentIndex(i);
            break;
        }
    }
}

void DialogTask::highlightSearch(QString pattern)
{
    ui->widgetRtfContent->highlightPattern(pattern);
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
    m_task->content = ui->widgetRtfContent->toHtml();
    m_task->priority = ui->comboBoxPriority->currentData(Qt::UserRole).toInt();
    if(m_task->id)
    {
        m_task->update();
        emit Bus::instance()->taskUpdated(m_task->id, m_task->project_id, old_project_id);
    }
    else
    {
        m_task->insert();
        emit Bus::instance()->taskUpdated(m_task->id, m_task->project_id, m_task->project_id);
    }
    this->accept();
}
