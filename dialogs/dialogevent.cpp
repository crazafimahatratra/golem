#include "dialogevent.h"
#include "ui_dialogevent.h"
#include "models/project.h"

DialogEvent::DialogEvent(int id, MainWindow *parent) :
    QDialog(parent),
    ui(new Ui::DialogEvent),
    m_parent(parent)
{
    ui->setupUi(this);

    m_event = Event::findById<Event>(id);
    if(!m_event) {
        m_event = new Event();
        m_event->id = 0;
        m_event->project_id = 0;
        m_event->evedate = QDateTime::currentDateTime();
    }

    QList<Project *> rows = Project::getAll<Project>();
    for(int i = 0; i < rows.length(); i++)
    {
        ui->comboBoxProjects->addItem(rows[i]->name, rows[i]->id);
        if(m_event->project_id == rows[i]->id)
            ui->comboBoxProjects->setCurrentIndex(i);
        delete rows[i];
    }

    ui->dateTimeEdit->setDateTime(m_event->evedate);
    ui->lineEditTitle->setText(m_event->title);
    ui->textEditContent->setHtml(m_event->content);
}

DialogEvent::~DialogEvent()
{
    delete ui;
}

void DialogEvent::on_pushButtonCancel_clicked()
{
    this->reject();
}

void DialogEvent::on_pushButtonOK_clicked()
{
    m_event->project_id = ui->comboBoxProjects->currentData(Qt::UserRole).toInt();
    m_event->title = ui->lineEditTitle->text();
    QDateTime old_date = m_event->evedate;
    int old_project_id = m_event->project_id;
    m_event->evedate = ui->dateTimeEdit->dateTime();
    m_event->content = ui->textEditContent->toHtml();
    if(m_event->id)
    {
        m_event->update();
        emit m_parent->eventUpdated(m_event->id, m_event->project_id, m_event->evedate, old_project_id, old_date);
    }
    else
    {
        m_event->insert();
        emit m_parent->eventUpdated(m_event->id, m_event->project_id, m_event->evedate, m_event->project_id, m_event->evedate);
    }
    this->accept();
}