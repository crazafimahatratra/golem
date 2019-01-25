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

    /**
     * @brief opens the window MdiProject when it is not opened yet, or activate it.
     * @param project_id : id of the project to be opened
     */
    void openProject(int project_id);

    /**
     * @brief the code to return when restarting application
     * @see QSqliteWrapper::Backup::importDb()
     */
    static int const EXIT_CODE_REBOOT;
signals:

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

    void on_taskDroped(int task_id, int project_id);

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
