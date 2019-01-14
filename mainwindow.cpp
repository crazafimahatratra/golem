#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogs/dialogcollection.h"
#include "dialogs/dialogproject.h"
#include "mdi/mdiproject.h"
#include "models/collection.h"
#include "models/project.h"
#include <QMessageBox>
#include <QMdiSubWindow>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_MenuTreeWidgetCollections(new QMenu(this)),
    m_MenuTreeWidgetEvents(new QMenu(this))
{
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);
    tabifyDockWidget(ui->dockWidget, ui->dockWidget_2);

    m_MenuTreeWidgetCollections->addAction(ui->actionNewCollection);
    m_MenuTreeWidgetCollections->addAction(ui->actionEdit_Collection);
    m_MenuTreeWidgetCollections->addAction(ui->actionRemove_Collection);
    m_MenuTreeWidgetCollections->addSeparator();
    m_MenuTreeWidgetCollections->addAction(ui->actionNewProject);
    m_MenuTreeWidgetCollections->addAction(ui->actionEdit_Project);
    m_MenuTreeWidgetCollections->addAction(ui->actionRemove_Project);
    fillTreeCollections();

    m_MenuTreeWidgetEvents->addAction(ui->actionNew_Event);

    connect(this, &MainWindow::collectionUpdated, this, &MainWindow::fillTreeCollections);
    connect(this, &MainWindow::collectionDeleted, this, &MainWindow::fillTreeCollections);
    connect(this, &MainWindow::projectUpdated, this, &MainWindow::fillTreeCollections);
    connect(this, &MainWindow::projectDeleted, this, &MainWindow::fillTreeCollections);
    connect(this, &MainWindow::taskUpdated, this, &MainWindow::fillTreeCollections);
    connect(this, &MainWindow::taskDeleted, this, &MainWindow::fillTreeCollections);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_Quitter_triggered()
{
    qApp->quit();
}

void MainWindow::on_actionNewCollection_triggered()
{
    DialogCollection dialog(0, this);
    dialog.exec();
}

void MainWindow::fillTreeCollections()
{
    QList<Collection *> rows = Collection::getAll<Collection>();
    ui->treeWidgetCollections->topLevelItem(0)->takeChildren();
    for(int i = 0; i < rows.length(); i++)
    {
        QTreeWidgetItem *item = new QTreeWidgetItem(TREEVIEW_TYPE_COLLECTION);
        item->setText(0, rows[i]->name);
        item->setData(0, Qt::UserRole, rows[i]->id);
        item->setIcon(0, QIcon(":/png/icons/box.png"));
        ui->treeWidgetCollections->topLevelItem(0)->addChild(item);
        delete rows[i];
    }

    QList<Project *> projects = Project::getAll<Project>();
    m_numTasksByProject = Task::countByProject();
    for(int i = 0; i < projects.length(); i++)
    {
        QTreeWidgetItem *root = this->treeWidgetItemFromValue(ui->treeWidgetCollections->topLevelItem(0), projects[i]->collection_id);
        if(root)
            this->addProjectToTree(root, projects[i]);
        delete projects[i];
    }
    ui->treeWidgetCollections->expandAll();
    this->updateMenus();
    for(int i = 0; i < ui->treeWidgetCollections->columnCount(); i++)
        ui->treeWidgetCollections->resizeColumnToContents(i);
}

void MainWindow::addProjectToTree(QTreeWidgetItem *root, Project *row)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(TREEVIEW_TYPE_PROJECT);
    item->setText(0, row->name);
    if(m_numTasksByProject[row->id])
    {
        item->setText(1, QString("(%1)").arg(m_numTasksByProject[row->id]));
        QFont f = item->font(1);
        f.setBold(true);
        item->setFont(1, f);
    }
    item->setData(0, Qt::UserRole, row->id);
    item->setIcon(0, QIcon(":/png/icons/folder.png"));
    root->addChild(item);
}

void MainWindow::updateMenus()
{
    bool collectionSelected = (ui->treeWidgetCollections->selectedItems().count() > 0) && (ui->treeWidgetCollections->currentItem()->type() == TREEVIEW_TYPE_COLLECTION);
    ui->actionEdit_Collection->setEnabled(collectionSelected);
    ui->actionRemove_Collection->setEnabled(collectionSelected);
    ui->actionNewProject->setEnabled(collectionSelected);
    bool projectSelected = (ui->treeWidgetCollections->selectedItems().count() > 0) && (ui->treeWidgetCollections->currentItem()->type() == TREEVIEW_TYPE_PROJECT);
    ui->actionEdit_Project->setEnabled(projectSelected);
    ui->actionRemove_Project->setEnabled(projectSelected);
}

void MainWindow::updateMdiTabbar()
{
    QList<QTabBar*> bars = ui->mdiArea->findChildren<QTabBar*>("", Qt::FindDirectChildrenOnly);
    for(int i = 0; i < bars.length(); i++)
    {
        bars[i]->setExpanding(false);
    }
}

void MainWindow::openProject(int project_id)
{
    MdiProject *win = nullptr;
    QList<QMdiSubWindow*> subwindows = ui->mdiArea->subWindowList();
    for(int i = 0; i < subwindows.length(); i++)
    {
        if (qobject_cast<MdiProject*> (subwindows[i]->widget()))
        {
            MdiProject *w = (MdiProject *)(subwindows[i]->widget());
            if(w->projectId() == project_id)
            {
                win = w;
                break;
            }
        }
    }
    if(!win)
    {
        win = new MdiProject(project_id, this);
        ui->mdiArea->addSubWindow(win);
    }
    win->showMaximized();
    this->updateMdiTabbar();
}

QTreeWidgetItem *MainWindow::treeWidgetItemFromValue(QTreeWidgetItem *root, int value)
{
    for(int i = 0; i < root->childCount(); i++)
    {
        if(root->child(i)->data(0, Qt::UserRole).toInt() == value)
            return root->child(i);
    }
    return NULL;
}

void MainWindow::on_treeWidgetCollections_itemSelectionChanged()
{
    this->updateMenus();
}

void MainWindow::on_treeWidgetCollections_customContextMenuRequested(const QPoint &pos)
{
    m_MenuTreeWidgetCollections->popup(ui->treeWidgetCollections->mapToGlobal(pos));
}

void MainWindow::on_actionNewProject_triggered()
{
    if(!ui->treeWidgetCollections->currentItem())
        return;
    int id = ui->treeWidgetCollections->currentItem()->data(0, Qt::UserRole).toInt();
    DialogProject dialog(id, 0, this);
    dialog.exec();
}

void MainWindow::on_actionEdit_Collection_triggered()
{
    int id = ui->treeWidgetCollections->currentItem()->data(0, Qt::UserRole).toInt();
    DialogCollection dialog(id, this);
    dialog.exec();
}

void MainWindow::on_actionRemove_Collection_triggered()
{
    int id = ui->treeWidgetCollections->currentItem()->data(0, Qt::UserRole).toInt();
    QString label = ui->treeWidgetCollections->currentItem()->text(0);
    int res = QMessageBox::critical(this, "Confirmation", "Delete the collection " + label + ".\n\n"
                                                          "The operation you are going to perform is dangerous.\n"
                                                          "Are you sure ?", QMessageBox::Yes|QMessageBox::No);
    if(res != QMessageBox::Yes)
        return;
    Collection *c = Collection::findById<Collection>(id);
    if(c) {
        c->remove();
        emit this->collectionDeleted(c->id);
        delete c;
    }
}

void MainWindow::on_actionEdit_Project_triggered()
{
    int id = ui->treeWidgetCollections->currentItem()->data(0, Qt::UserRole).toInt();
    DialogProject dialog(0, id, this);
    dialog.exec();
}

void MainWindow::on_actionRemove_Project_triggered()
{
    int id = ui->treeWidgetCollections->currentItem()->data(0, Qt::UserRole).toInt();
    QString label = ui->treeWidgetCollections->currentItem()->text(0);
    int res = QMessageBox::warning(this, "Confirmation", "Delete the project " + label + ".\n\n"
                                                          "The operation you are going to perform is dangerous.\n"
                                                          "Are you sure ?", QMessageBox::Yes|QMessageBox::No);
    if(res != QMessageBox::Yes)
        return;
    Project *p = Project::findById<Project>(id);
    if(p) {
        p->remove();
        emit this->projectDeleted(p->id);
        delete p;
    }
}

void MainWindow::on_treeWidgetCollections_itemDoubleClicked(QTreeWidgetItem *item, int)
{
    if(item->type() != TREEVIEW_TYPE_PROJECT)
        return;
    int id = item->data(0, Qt::UserRole).toInt();
    this->openProject(id);
}

void MainWindow::on_treeWidgetEvents_customContextMenuRequested(const QPoint &pos)
{
    m_MenuTreeWidgetEvents->popup(ui->treeWidgetEvents->mapToGlobal(pos));
}
