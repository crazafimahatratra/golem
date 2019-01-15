#include "mdievents.h"
#include "ui_mdievents.h"
#include "dialogs/dialogevent.h"
#include <QDebug>
#include <QMessageBox>
#include "qtkit/WidgetUtils/treewidget.h"

MdiEvents::MdiEvents(QDate date, MainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::MdiEvents),
    m_date(date),
    m_parent(parent),
    m_menuEvents(new QMenu(this))
{
    ui->setupUi(this);
    setWindowTitle("Events " + m_date.toString("yyyy-MM-dd"));
    fillEvents();
    connect(m_parent, &MainWindow::eventUpdated, this, &MdiEvents::on_eventUpdated);
    connect(m_parent, &MainWindow::eventDeleted, this, &MdiEvents::on_eventDeleted);

    m_menuEvents->addAction(ui->actionNew_Event);
    m_menuEvents->addAction(ui->actionEdit_Event);
    m_menuEvents->addAction(ui->actionRemove_Event);
}

MdiEvents::~MdiEvents()
{
    delete ui;
}

QDate MdiEvents::date()
{
    return m_date;
}

void MdiEvents::cleanTopLevelItems()
{
    while(ui->treeWidget->topLevelItemCount())
    {
        ui->treeWidget->topLevelItem(0)->takeChildren();
        ui->treeWidget->takeTopLevelItem(0);
    }
}

void MdiEvents::addProjectsToTree()
{
    QList<Project *> projects = Project::getAll<Project>();
    for(int i = 0; i < projects.length(); i++)
    {
        QTreeWidgetItem *item = new QTreeWidgetItem(TREEVIEW_TYPE_PROJECT);
        item->setText(0, projects[i]->name);
        item->setData(0, Qt::UserRole, projects[i]->id);
        item->setIcon(0, QIcon(":/png/icons/folder.png"));
        ui->treeWidget->addTopLevelItem(item);
        delete projects[i];
    }
}

void MdiEvents::cleanEmptyProjects()
{
    for(int i = 0; i < ui->treeWidget->topLevelItemCount(); i++)
    {
        QTreeWidgetItem *root = ui->treeWidget->topLevelItem(i);
        root->setHidden(root->childCount() == 0);
    }
    ui->treeWidget->expandAll();
    WidgetUtils::TreeWidget::resizeColumns(ui->treeWidget);
}

void MdiEvents::fillEvents()
{
    cleanTopLevelItems();
    addProjectsToTree();
    QDateTime d0 = QDateTime(m_date);
    QDateTime d1 = d0.addDays(1);
    Event *model = new Event();
    model->where("evedate >=", d0);
    model->where("evedate < ", d1);
    QList<Event *> rows = model->get<Event>();
    for(int i = 0; i < rows.length(); i++)
    {
        addEventToTree(rows[i]);
        delete rows[i];
    }
    delete model;
    cleanEmptyProjects();
    updateMenu();
}

void MdiEvents::addEventToTree(Event *row)
{
    for(int i = 0; i < ui->treeWidget->topLevelItemCount(); i++)
    {
        QTreeWidgetItem *root = ui->treeWidget->topLevelItem(i);
        if(root->data(0, Qt::UserRole).toInt() == row->project_id)
        {
            QTreeWidgetItem *item = new QTreeWidgetItem(TREEVIEW_TYPE_EVENT);
            item->setText(0, row->evedate.toString("yyyy-MM-dd HH:mm:ss"));
            item->setText(1, row->title);
            item->setData(0, Qt::UserRole, row->id);
            root->addChild(item);
            break;
        }
    }
}

int MdiEvents::selectedEventId()
{
    if(!ui->treeWidget->currentItem())
        return 0;
    if(ui->treeWidget->currentItem()->type() != TREEVIEW_TYPE_EVENT)
        return 0;
    return ui->treeWidget->currentItem()->data(0, Qt::UserRole).toInt();
}

QString MdiEvents::selectedEventTitle()
{
    if(!ui->treeWidget->currentItem())
        return "";
    if(ui->treeWidget->currentItem()->type() != TREEVIEW_TYPE_EVENT)
        return "";
    return ui->treeWidget->currentItem()->text(0);
}

void MdiEvents::on_actionNew_Event_triggered()
{
    DialogEvent dialog(0, m_parent);
    dialog.exec();
}

void MdiEvents::on_eventUpdated(int, int, QDateTime, int, QDateTime old_date)
{
    if(old_date.date() == this->m_date)
    {
        this->fillEvents();
    }
}

void MdiEvents::on_eventDeleted(int, int, QDateTime date)
{
    if(date.date() == this->m_date)
    {
        this->fillEvents();
    }
}

void MdiEvents::on_actionRemove_Event_triggered()
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

void MdiEvents::on_actionEdit_Event_triggered()
{
    int id = selectedEventId();
    if(!id)
        return;
    DialogEvent dialog(id, m_parent);
    dialog.exec();
}

void MdiEvents::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *, int)
{
    on_actionEdit_Event_triggered();
}

void MdiEvents::updateMenu()
{
    bool eventSelected = selectedEventId() > 0;
    ui->actionEdit_Event->setEnabled(eventSelected);
    ui->actionRemove_Event->setEnabled(eventSelected);
}

void MdiEvents::on_treeWidget_itemSelectionChanged()
{
    updateMenu();
}

void MdiEvents::on_treeWidget_customContextMenuRequested(const QPoint &pos)
{
    m_menuEvents->popup(ui->treeWidget->mapToGlobal(pos));
}
