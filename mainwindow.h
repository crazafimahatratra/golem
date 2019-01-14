#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QMap>
#include <QDateTime>
#include "models/project.h"
#define TREEVIEW_TYPE_COLLECTION 1
#define TREEVIEW_TYPE_PROJECT 2
#define TREEVIEW_TYPE_YEAR 3
#define TREEVIEW_TYPE_MONTH 4
#define TREEVIEW_TYPE_DAY 5
#define TREEVIEW_TYPE_EVENT 6

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
signals:
    void projectUpdated(int project_id);
    void projectDeleted(int project_id);
    void collectionUpdated(int collection_id);
    void collectionDeleted(int collection_id);
    void taskUpdated(int task_id, int project_id, int old_project_id);
    void taskDeleted(int task_id, int project_id);
    void eventUpdated(int event_id, int project_id, QDateTime date, int old_project_id, QDateTime old_date);
    void eventDeleted(int event_id, int project_id, QDateTime date);

private slots:
    void on_action_Quitter_triggered();

    void on_actionNewCollection_triggered();

    void on_treeWidgetCollections_itemSelectionChanged();

    void on_treeWidgetCollections_customContextMenuRequested(const QPoint &pos);

    void on_actionNewProject_triggered();

    void on_actionEdit_Collection_triggered();

    void on_actionRemove_Collection_triggered();

    void on_actionEdit_Project_triggered();

    void on_actionRemove_Project_triggered();

    void on_treeWidgetCollections_itemDoubleClicked(QTreeWidgetItem *item, int);

    void on_treeWidgetEvents_customContextMenuRequested(const QPoint &pos);

    void on_actionNew_Event_triggered();

    void on_treeWidgetEvents_itemDoubleClicked(QTreeWidgetItem *item, int);

private:
    Ui::MainWindow *ui;
    QMenu *m_MenuTreeWidgetCollections;
    QMenu *m_MenuTreeWidgetEvents;
    QMap<int, int> m_numTasksByProject;
    void fillTreeCollections();
    void fillTreeEvents();
    void addProjectToTree(QTreeWidgetItem *root, Project *row);
    void addEventToTree(QTreeWidgetItem *root, QDate date);
    void updateMenus();
    void updateMdiTabbar();
    void openProject(int project_id);
    void openEvents(QDate date);
    QTreeWidgetItem *treeWidgetItemFromValue(QTreeWidgetItem *root, int value);
};

#endif // MAINWINDOW_H
