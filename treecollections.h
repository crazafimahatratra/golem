#ifndef TREECOLLECTIONS_H
#define TREECOLLECTIONS_H

#include <QWidget>
#include <QTreeWidget>
#include <QMimeData>
#include <QDropEvent>

/**
 * @brief Base class for the tree widget containing projects and collections
 */
class TreeCollections : public QTreeWidget
{
    Q_OBJECT
public:
    /**
     * @brief Constructor
     * @param parent : the parent widget
     */
    explicit TreeCollections(QWidget *parent = nullptr);

signals:
    /**
     * @brief raised when a task is droped on the tree item
     * @param task_id : the id of the task droped
     * @param project_id : the id of the project in the item
     */
    void taskDroped(int task_id, int project_id);

public slots:

    // QTreeWidget interface
protected:
    /**
     * @brief alled when something is dropped upon the widget
     * @param parent : the parent node of the item
     * @param index : index of the item
     * @param data : the data dropped
     * @param action : action
     * @return
     */
    bool dropMimeData(QTreeWidgetItem *parent, int index, const QMimeData *data, Qt::DropAction action);
};

#endif // TREECOLLECTIONS_H
