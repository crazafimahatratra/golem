#include "mdiproject.h"
#include "ui_mdiproject.h"
#include "dialogs/dialogtask.h"
#include "dialogs/dialogevent.h"
#include "constants.h"
#include <QMessageBox>
#include <QDebug>
#include "qtkit/WidgetUtils/tablewidget.h"
#include "qtkit/WidgetUtils/treewidget.h"

MdiProject::MdiProject(int id, MainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::MdiProject),
    m_parent(parent)
{
    ui->setupUi(this);

    updateProject(id);
    this->fillTasks();
    this->fillEvents();

    m_menuTasks =  new QMenu(this);
    m_menuTasks->addAction(ui->actionNewTask);
    m_menuTasks->addAction(ui->actionEdit_Task);
    m_menuTasks->addAction(ui->actionRemove_Task);
    m_menuTasks->addSeparator();
    m_menuTasks->addAction(ui->actionMark_As_Done);
    m_menuTasks->addAction(ui->actionRestart);

    m_menuEvents = new QMenu(this);
    m_menuEvents->addAction(ui->actionNew_Event);
    m_menuEvents->addAction(ui->actionEdit_Event);
    m_menuEvents->addAction(ui->actionRemove_Event);

    connect(m_parent, &MainWindow::collectionUpdated, this, &MdiProject::on_collectionUpdated);
    connect(m_parent, &MainWindow::collectionDeleted, this, &MdiProject::on_collectionDeleted);
    connect(m_parent, &MainWindow::projectUpdated, this, &MdiProject::on_projectUpdated);
    connect(m_parent, &MainWindow::projectDeleted, this, &MdiProject::on_projectDeleted);
    connect(m_parent, &MainWindow::taskUpdated, this, &MdiProject::on_taskUpdated);
    connect(m_parent, &MainWindow::taskDeleted, this, &MdiProject::on_taskDeleted);
    connect(m_parent, &MainWindow::eventUpdated, this, &MdiProject::on_eventUpdated);
    connect(m_parent, &MainWindow::eventDeleted, this, &MdiProject::on_eventDeleted);
}

MdiProject::~MdiProject()
{
    if(m_project)
        delete m_project;
    if(m_collection)
        delete m_collection;
    delete m_menuTasks;
    delete ui;
}

void MdiProject::on_actionNewTask_triggered()
{
    DialogTask dialog(m_project->id, 0, m_parent);
    dialog.exec();
}

void MdiProject::fillTasks()
{
    Task *model = new Task();
    model->where("project_id = ", this->m_project->id);
    if(!ui->actionShow_All_History->isChecked())
    {
        model->startGroup();
        model->where("duedate >=", QDate::currentDate());
        model->where("status != ", TASK_STATUS_FINISHED, "OR");
        model->endGroup();
    }
    model->order("duedate DESC");
    QList<Task *> rows = model->get<Task>();
    QTreeWidgetItem *root = ui->treeWidget->topLevelItem(0);
    for(int i = 0; i < ui->treeWidget->topLevelItemCount(); i++)
        ui->treeWidget->topLevelItem(i)->takeChildren();
    for(int i = 0; i < rows.length(); i++)
    {
        QTreeWidgetItem *item = new QTreeWidgetItem(TREEVIEW_TYPE_TASK);
        item->setData(0, Qt::UserRole, rows[i]->id);
        item->setData(0, Qt::UserRole + 1, rows[i]->status);
        item->setText(0, rows[i]->title);
        item->setText(1, rows[i]->dueDate.toString(DATETIME_FORMAT));
        if(rows[i]->status == TASK_STATUS_FINISHED) {
            item->setIcon(0, QIcon(":/png/icons/tick.png"));
        } else {
            item->setIcon(0, QIcon(":/png/icons/clock.png"));
        }
        Task::timelineCategory category = rows[i]->getTimelineCategory();
        root = ui->treeWidget->topLevelItem(category);
        if(category == Task::Overdue)
        {
            item->setTextColor(0, QColor("red"));
            item->setTextColor(1, QColor("red"));
        }
        root->addChild(item);
        delete rows[i];
    }
    delete model;
    this->updateMenuTasks();
    ui->treeWidget->expandAll();

    for(int i = 0; i < ui->treeWidget->topLevelItemCount(); i++)
    {
        QTreeWidgetItem *root = ui->treeWidget->topLevelItem(i);
        root->setHidden(root->childCount() == 0);
    }

    WidgetUtils::TreeWidget::resizeColumns(ui->treeWidget);
}

void MdiProject::fillEvents()
{
    Event *model = new Event();
    model->where("project_id = ", this->m_project->id)->order("evedate DESC");
    QList<Event *> rows = model->get<Event>();
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(rows.length());
    for(int i = 0; i < rows.length(); i++)
    {
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(rows[i]->evedate.toString(DATETIME_FORMAT)));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(rows[i]->title));
        ui->tableWidget->item(i, 0)->setData(Qt::UserRole, rows[i]->id);
        delete rows[i];
    }
    for(int i = 0; i < ui->tableWidget->columnCount() - 1; i++)
        ui->tableWidget->resizeColumnToContents(i);
    delete model;
    WidgetUtils::TableWidget::setReadonly(ui->tableWidget);
    updateMenuEvents();
}

int MdiProject::selectedTaskId()
{
    if(!ui->treeWidget->currentItem())
        return 0;
    if(ui->treeWidget->currentItem()->type() != TREEVIEW_TYPE_TASK)
        return 0;
    return ui->treeWidget->currentItem()->data(0, Qt::UserRole).toInt();
}

int MdiProject::selectedEventId()
{
    if(ui->tableWidget->currentRow() < 0)
        return 0;
    return ui->tableWidget->item(ui->tableWidget->currentRow(), 0)->data(Qt::UserRole).toInt();
}

QString MdiProject::selectedTaskTitle()
{
    if(!ui->treeWidget->currentItem())
        return "";
    if(ui->treeWidget->currentItem()->type() != TREEVIEW_TYPE_TASK)
        return "";
    return ui->treeWidget->currentItem()->text(0);
}

QString MdiProject::selectedEventTitle()
{
    if(ui->tableWidget->currentRow() < 0)
        return "";
    return ui->tableWidget->item(ui->tableWidget->currentRow(), 1)->text();
}

int MdiProject::selectedTaskStatus()
{
    if(!ui->treeWidget->currentItem())
        return 0;
    if(ui->treeWidget->currentItem()->type() != TREEVIEW_TYPE_TASK)
        return 0;
    return ui->treeWidget->currentItem()->data(0, Qt::UserRole + 1).toInt();
}

void MdiProject::on_actionRemove_Task_triggered()
{
    int id = selectedTaskId();
    if(!id)
        return;
    QString label = selectedTaskTitle();
    int res = QMessageBox::warning(this, "Confirmation", "Delete the task " + label + ".\n\n"
                                                          "Are you sure ?", QMessageBox::Yes|QMessageBox::No);
    if(res != QMessageBox::Yes)
        return;
    Task *p = Task::findById<Task>(id);
    if(p) {
        p->remove();
        emit m_parent->taskDeleted(p->id, p->project_id);
        delete p;
    }
}

void MdiProject::on_actionEdit_Task_triggered()
{
    int id = selectedTaskId();
    if(!id)
        return;
    DialogTask dialog(m_project->id, id, m_parent);
    dialog.exec();
}

void MdiProject::updateMenuTasks()
{
    bool taskSelected = selectedTaskId() > 0;
    int status = selectedTaskStatus();
    ui->actionEdit_Task->setEnabled(taskSelected);
    ui->actionRemove_Task->setEnabled(taskSelected);
    ui->actionMark_As_Done->setEnabled(taskSelected && (status == TASK_STATUS_STARTED));
    ui->actionRestart->setEnabled(taskSelected && (status == TASK_STATUS_FINISHED));


}

void MdiProject::updateMenuEvents()
{
    bool eventSelected = selectedEventId() > 0;
    ui->actionEdit_Event->setEnabled(eventSelected);
    ui->actionRemove_Event->setEnabled(eventSelected);
}

void MdiProject::updateProject(int project_id)
{
    m_project = Project::findById<Project>(project_id);
    if(!m_project)
    {
        this->parentWidget()->close();
        return;
    }
    m_collection = Collection::findById<Collection>(m_project->collection_id);
    if(!m_collection)
    {
        this->parentWidget()->close();
        return;
    }
    this->setWindowTitle(QString("%1 - %2").arg(m_collection->name, m_project->name));
    ui->labelCollectionName->setText(m_collection->name);
    ui->labelProjectName->setText(m_project->name);
}

void MdiProject::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *, int)
{
    this->on_actionEdit_Task_triggered();
}

void MdiProject::on_treeWidget_customContextMenuRequested(const QPoint &pos)
{
    m_menuTasks->popup(ui->treeWidget->mapToGlobal(pos));
}

void MdiProject::on_treeWidget_itemSelectionChanged()
{
    this->updateMenuTasks();
}

void MdiProject::on_actionMark_As_Done_triggered()
{
    int id = this->selectedTaskId();
    if(!id)
        return;
    Task *t = Task::findById<Task>(id);
    if(!t)
        return;
    t->status = TASK_STATUS_FINISHED;
    t->update();
    emit m_parent->taskUpdated(t->id, t->project_id, t->project_id);
    delete t;
}


void MdiProject::on_actionRestart_triggered()
{
    int id = this->selectedTaskId();
    if(!id)
        return;
    Task *t = Task::findById<Task>(id);
    if(!t)
        return;
    t->status = TASK_STATUS_STARTED;
    t->update();
    emit m_parent->taskUpdated(t->id, t->project_id, t->project_id);
    delete t;
}

void MdiProject::on_actionShow_All_History_triggered()
{
    this->fillTasks();
}

void MdiProject::on_collectionUpdated(int collection_id)
{
    if(collection_id != m_project->collection_id)
        return;
    delete m_collection;
    updateProject(m_project->id);
}

void MdiProject::on_collectionDeleted(int collection_id)
{
    if(collection_id != m_project->collection_id)
        return;
    this->parentWidget()->close();
}

void MdiProject::on_projectUpdated(int project_id)
{
    if(project_id != m_project->id)
        return;
    delete m_collection;
    delete m_project;
    updateProject(project_id);
}

void MdiProject::on_projectDeleted(int project_id)
{
    if(project_id != m_project->id)
        return;
    this->parentWidget()->close();
}

void MdiProject::on_taskUpdated(int, int project_id, int old_project_id)
{
    if((old_project_id != m_project->id) && (project_id != m_project->id))
        return;
    this->fillTasks();
}

void MdiProject::on_taskDeleted(int, int project_id)
{
    if(project_id != m_project->id)
        return;
    this->fillTasks();
}

void MdiProject::on_eventUpdated(int, int project_id, QDateTime, int old_project_id, QDateTime)
{
    if((old_project_id != m_project->id) && (project_id != m_project->id))
        return;
    this->fillEvents();
}

void MdiProject::on_eventDeleted(int, int project_id, QDateTime)
{
    if(project_id != m_project->id)
        return;
    this->fillEvents();
}

void MdiProject::on_tableWidget_cellDoubleClicked(int, int)
{
    on_actionEdit_Event_triggered();
}

void MdiProject::on_actionNew_Event_triggered()
{
    DialogEvent dialog(0, m_parent);
    dialog.setSelectedProject(m_project->id);
    dialog.exec();
}

void MdiProject::on_tableWidget_itemSelectionChanged()
{
    updateMenuEvents();
}

void MdiProject::on_actionEdit_Event_triggered()
{
    int id = selectedEventId();
    if(!id)
        return;
    DialogEvent dialog(id, m_parent);
    dialog.exec();
}

void MdiProject::on_actionRemove_Event_triggered()
{
    int id = selectedEventId();
    if(!id)
        return;
    QString label = selectedEventTitle();
    int res = QMessageBox::warning(this, "Confirmation", "Delete the event " + label + ".\n\n"
                                                          "Are you sure ?", QMessageBox::Yes|QMessageBox::No);
    if(res != QMessageBox::Yes)
        return;
    Event *p = Event::findById<Event>(id);
    if(p) {
        p->remove();
        emit m_parent->eventDeleted(p->id, p->project_id, p->evedate);
        delete p;
    }
}
