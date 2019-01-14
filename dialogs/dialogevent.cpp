#include "dialogevent.h"
#include "ui_dialogevent.h"
#include "models/project.h"

DialogEvent::DialogEvent(MainWindow *parent) :
    QDialog(parent),
    ui(new Ui::DialogEvent),
    m_parent(parent)
{
    ui->setupUi(this);
    QList<Project *> rows = Project::getAll<Project>();
    for(int i = 0; i < rows.length(); i++)
    {
        ui->comboBoxProjects->addItem(rows[i]->name, rows[i]->id);
        delete rows[i];
    }
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
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
    this->accept();
}
