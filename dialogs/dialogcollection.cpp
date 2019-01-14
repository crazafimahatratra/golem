#include "dialogcollection.h"
#include "ui_dialogcollection.h"
#include "models/collection.h"

DialogCollection::DialogCollection(int collection_id, MainWindow *parent) :
    QDialog(parent),
    ui(new Ui::DialogCollection),
    m_parent(parent)
{
    ui->setupUi(this);
    m_collection = Collection::findById<Collection>(collection_id);
    if(!m_collection)
    {
        m_collection = new Collection();
        m_collection->id = 0;
    }
    ui->lineEditName->setText(m_collection->name);
}

DialogCollection::~DialogCollection()
{
    delete m_collection;
    delete ui;
}

void DialogCollection::on_pushButtonOK_clicked()
{
    m_collection->name = ui->lineEditName->text();
    if(m_collection->id)
        m_collection->update();
    else
        m_collection->insert();
    emit m_parent->collectionUpdated(m_collection->id);
    this->accept();
}

void DialogCollection::on_pushButtonCancel_clicked()
{
    this->reject();
}
