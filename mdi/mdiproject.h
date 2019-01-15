#ifndef MDIPROJECT_H
#define MDIPROJECT_H

#include <QMainWindow>
#include <QMenu>
#include <QTreeWidgetItem>
#include "models/project.h"
#include "models/collection.h"
#include "models/task.h"
#include "models/event.h"
#include "mainwindow.h"

#define TREEVIEW_TYPE_TASK 1

namespace Ui {
class MdiProject;
}

class MdiProject : public QMainWindow
{
    Q_OBJECT

public:
    explicit MdiProject(int id, MainWindow *parent = 0);
    ~MdiProject();
    int projectId() {
        if(m_project)
            return m_project->id;
        return 0;
    }
signals:
    void requestClose();

private slots:
    void on_actionNewTask_triggered();

    void on_actionRemove_Task_triggered();

    void on_actionEdit_Task_triggered();

    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *, int);

    void on_treeWidget_customContextMenuRequested(const QPoint &pos);

    void on_treeWidget_itemSelectionChanged();

    void on_actionMark_As_Done_triggered();

    void on_actionRestart_triggered();

    void on_actionShow_All_History_triggered();

    void on_collectionUpdated(int collection_id);

    void on_collectionDeleted(int collection_id);

    void on_projectUpdated(int project_id);

    void on_projectDeleted(int project_id);

    void on_taskUpdated(int, int project_id, int old_project_id);

    void on_taskDeleted(int, int project_id);

    void on_eventUpdated(int, int project_id, QDateTime, int old_project_id, QDateTime);

    void on_tableWidget_cellDoubleClicked(int row, int);

private:
    Ui::MdiProject *ui;
    MainWindow *m_parent;
    Project *m_project = nullptr;
    Collection *m_collection = nullptr;
    QMenu *m_menuTasks = nullptr;
    void updateMenu();
    void updateProject(int project_id);
    void fillTasks();
    void fillEvents();
    int selectedTaskId();
    QString selectedTaskTitle();
    int selectedTaskStatus();
};

#endif // MDIPROJECT_H
