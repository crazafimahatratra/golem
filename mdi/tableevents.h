#ifndef TABLEEVENTS_H
#define TABLEEVENTS_H

#include <QWidget>
#include <QTableWidget>
#include <QMimeData>
#include <QDropEvent>

/**
 * @brief Base class for the table widget containing events
 */
class TableEvents : public QTableWidget
{
    Q_OBJECT
public:
    /**
     * @brief Constructor
     * @param parent : the parent widget
     */
    explicit TableEvents(QWidget *parent = nullptr);

signals:
    /**
     * @brief raised when a task is dropped on the widget
     * @param id : the id of the task. Task::id
     */
    void taskReceived(int id);

public slots:

    // QTableWidget interface
protected:
    /**
     * @brief dropMimeData called when something is dropped upon the widget
     * @param data : the data :)
     * @return boolean saying if data was accepted or not.
     */
    bool dropMimeData(int, int, const QMimeData *data, Qt::DropAction);
};

#endif // TABLEEVENTS_H
