#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QMap>
#include "models/project.h"
#define TREEVIEW_TYPE_COLLECTION 1
#define TREEVIEW_TYPE_PROJECT 2

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
    void taskUpdated(int task_id, int project_id);
    void taskDeleted(int task_id, int project_id);

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

private:
    Ui::MainWindow *ui;
    QMenu *m_MenuTreeWidgetCollections;
    QMap<int, int> m_numTasksByProject;
    void fillTreeCollections();
    void addProjectToTree(QTreeWidgetItem *root, Project *row);
    void updateMenus();
    void updateMdiTabbar();
    void openProject(int project_id);
    QTreeWidgetItem *treeWidgetItemFromValue(QTreeWidgetItem *root, int value);
};

#endif // MAINWINDOW_H
