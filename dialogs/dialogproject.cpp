#include "dialogproject.h"
#include "ui_dialogproject.h"
#include "models/collection.h"
#include "models/project.h"
#include "bus.h"

DialogProject::DialogProject(int collection_id, int project_id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogProject)
{
    ui->setupUi(this);
    if(project_id)
    {
        m_project = Project::findById<Project>(project_id);
        if(m_project)
        {
            collection_id = m_project->collection_id;
            ui->lineEditName->setText(m_project->name);
        }
    }

    if(!m_project) {
        m_project = new Project();
        m_project->id = 0;
    }

    Collection *model = new Collection();
    model->order("name");
    QList<Collection *> rows = model->get<Collection>();
    delete model;
    for(int i = 0; i < rows.length(); i++)
    {
        ui->comboBoxCollections->addItem(rows[i]->name, rows[i]->id);
        if(collection_id == rows[i]->id)
            ui->comboBoxCollections->setCurrentIndex(i);
        delete rows[i];
    }
}

DialogProject::~DialogProject()
{
    delete m_project;
    delete ui;
}

void DialogProject::on_pushButtonOK_clicked()
{
    m_project->name = ui->lineEditName->text();
    m_project->color = "000000";
    m_project->collection_id = ui->comboBoxCollections->currentData(Qt::UserRole).toInt();
    if(m_project->id)
        m_project->update();
    else
        m_project->insert();
    emit Bus::instance()->projectUpdated(m_project->id);
    this->accept();
}

void DialogProject::on_pushButtonCancel_clicked()
{
    this->reject();
}
