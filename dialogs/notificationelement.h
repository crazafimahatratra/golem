#ifndef NOTIFICATIONELEMENT_H
#define NOTIFICATIONELEMENT_H

#include <QWidget>
#include "models/task.h"
#include "models/project.h"

namespace Ui {
class NotificationElement;
}

/**
 * @brief The NotificationElement class is a widget representing one notification
 * It is associated to one Task
 */
class NotificationElement : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     * @param parent : the parent widget
     */
    explicit NotificationElement(QWidget *parent = 0);
    ~NotificationElement();

    /**
     * @brief sets the task associated to the widget NotificationElement
     * @param task : the task to be associated
     */
    void setTask(Task *task);

    /**
     * @brief returns the id of the Task associated to the widget
     * @return Task::id
     */
    int taskId();

signals:
    /**
     * @brief raised when the user clicks on the button **Done**
     * @param task_id : the id of the Task associated to the widget
     */
    void taskDone(int task_id);

    /**
     * @brief raised when the user clicks on the button **More**
     * @param task_id : the id of the Task associated to the widget
     */
    void taskDetailsRequested(int task_id);

private slots:
    void on_pushButtonDone_clicked();

    void on_pushButtonGo_clicked();

private:
    Ui::NotificationElement *ui;
    int m_taskid;
};

#endif // NOTIFICATIONELEMENT_H
