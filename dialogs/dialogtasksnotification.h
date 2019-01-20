#ifndef DIALOGTASKSNOTIFICATION_H
#define DIALOGTASKSNOTIFICATION_H

#include <QDialog>
#include "models/task.h"

namespace Ui {
class DialogTasksNotification;
}

/**
 * @brief Represents the popup shown when there are notifications about a non completed Task
 */
class DialogTasksNotification : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     * @param parent : the parent widget
     */
    explicit DialogTasksNotification(QWidget *parent = 0);
    ~DialogTasksNotification();

    /**
     * @brief adds a Task to be shown on the popup if it does not exists yet in the stack.
     * @param task : the task to be added
     */
    void showTask(Task *task);

    /**
     * @brief Computes the bottom-right edge position of its parent (MainWindow)
     * and positions itself upon that coordinates.
     *
     * Should be called everytime the parent window gets moved.
     */
    void resetPosition();

private slots:
    void on_pushButtonPrev_clicked();

    void on_pushButtonNext_clicked();

    void on_taskDone(int task_id);

    void on_taskDetailsRequested(int task_id);

    void on_taskDeleted(int task_id, int);

    void on_taskUpdated(int task_id, int, int);

private:
    Ui::DialogTasksNotification *ui;
    void updateLabelPage();
    int taskId(int index);
    int taskIndex(int task_id);
};

#endif // DIALOGTASKSNOTIFICATION_H
