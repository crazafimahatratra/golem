#ifndef MDIEVENTS_H
#define MDIEVENTS_H

#include <QMainWindow>
#include <QDateTime>
#include <QMenu>
#include "mainwindow.h"
#include "models/event.h"
#include "models/project.h"
#include "constants.h"

namespace Ui {
class MdiEvents;
}

class MdiEvents : public QMainWindow
{
    Q_OBJECT

public:
    explicit MdiEvents(QDate date, MainWindow *parent = 0);
    ~MdiEvents();
    QDate date();

private slots:
    void on_actionNew_Event_triggered();

    void on_eventUpdated(int, int, QDateTime, int, QDateTime old_date);

    void on_eventDeleted(int, int, QDateTime date);

    void on_actionRemove_Event_triggered();

    void on_actionEdit_Event_triggered();

    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *, int);

    void on_treeWidget_itemSelectionChanged();

    void on_treeWidget_customContextMenuRequested(const QPoint &pos);

private:
    Ui::MdiEvents *ui;
    QDate m_date;
    MainWindow *m_parent;
    QMenu *m_menuEvents = nullptr;
    void updateMenu();
    void cleanTopLevelItems();
    void addProjectsToTree();
    void cleanEmptyProjects();
    void fillEvents();
    void addEventToTree(Event *row);
    int selectedEventId();
    QString selectedEventTitle();
};

#endif // MDIEVENTS_H
