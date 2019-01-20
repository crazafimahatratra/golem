#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QMap>
#include <QDateTime>
#include <QLabel>
#include <QMoveEvent>
#include "models/project.h"
#include "models/task.h"
#include "updatemanager.h"
#include "notifierthread.h"
#include "dialogs/dialogtasksnotification.h"

#define TREEVIEW_TYPE_COLLECTION 1
#define TREEVIEW_TYPE_PROJECT 2
#define TREEVIEW_TYPE_YEAR 3
#define TREEVIEW_TYPE_MONTH 4
#define TREEVIEW_TYPE_DAY 5
#define TREEVIEW_TYPE_EVENT 6

/**
 * @namespace Ui Contains all User interfaces classes
 */
namespace Ui {
class MainWindow;
}

/**
 * @brief This is the main window
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     * @param parent widget
     */
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void openProject(int project_id);

    /**
     * @brief the code to return when restarting application
     * @see QSqliteWrapper::Backup::importDb()
     */
    static int const EXIT_CODE_REBOOT;
signals:
    /**
     * @brief called when a project has been updated or created
     * @param project_id : id of the project
     */
    void projectUpdated(int project_id);

    /**
     * @brief when a project has been deleted
     * @param project_id : id of the project
     */
    void projectDeleted(int project_id);

    /**
     * @brief when a collection has been updated or inserted
     * @param collection_id : id of the collection
     */
    void collectionUpdated(int collection_id);

    /**
     * @brief when a collection has been deleted
     * @param collection_id : id of the collection
     */
    void collectionDeleted(int collection_id);

    /**
     * @brief when a task has been updated or deleted
     * @param task_id : id of the task
     * @param project_id : id of the project
     * @param old_project_id : id of the previous project (if changed)
     */
    void taskUpdated(int task_id, int project_id, int old_project_id);

    /**
     * @brief when a task has been deleted
     * @param task_id : id of the task
     * @param project_id : id of the project
     */
    void taskDeleted(int task_id, int project_id);

    /**
     * @brief when an event have been updated or created
     * @param event_id : id of the event
     * @param project_id : id of the project
     * @param date : event date
     * @param old_project_id : id of the previous project (if changed)
     * @param old_date : this holds the previous date if it was changed
     */
    void eventUpdated(int event_id, int project_id, QDateTime date, int old_project_id, QDateTime old_date);

    /**
     * @brief when an event has been deleted
     * @param event_id : id of the event
     * @param project_id : id of the project
     * @param date : event date
     */
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

    void on_treeWidgetEvents_itemDoubleClicked(QTreeWidgetItem *item, int);

    void on_actionExport_Database_triggered();

    void on_actionImport_Database_triggered();

    void on_actionAbout_triggered();

    void on_lineEditFilterEvents_textChanged(const QString &arg1);

    void on_lineEditCollections_textChanged(const QString &arg1);

    void on_versionFetched(bool newer, QString version);

    void on_versionFetchError(QString error);

    void on_taskDueDateReached(Task *task);

private:
    Ui::MainWindow *ui;
    QMenu *m_MenuTreeWidgetCollections;
    QMenu *m_MenuTreeWidgetEvents;
    QMap<int, int> m_numTasksByProject;
    UpdateManager *m_updatemanager;
    NotifierThread *m_notifier;
    QLabel *m_labelnotification;
    DialogTasksNotification *m_dialognotification;

    void fillTreeCollections();
    void fillTreeEvents();
    void addProjectToTree(QTreeWidgetItem *root, Project *row);
    void addEventToTree(QTreeWidgetItem *root, QDate date);
    void updateMenus();
    void updateMdiTabbar();
    void openEvents(QDate date);
    QTreeWidgetItem *treeWidgetItemFromValue(QTreeWidgetItem *root, int value);

    void moveEvent(QMoveEvent *event);
};

#endif // MAINWINDOW_H
