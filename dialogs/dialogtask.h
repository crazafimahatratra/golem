#ifndef DIALOGTASK_H
#define DIALOGTASK_H

#include <QDialog>
#include "models/project.h"
#include "models/task.h"

namespace Ui {
class DialogTask;
}

/**
 * @brief Dialog for creating or editing a task
 */
class DialogTask : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     * @param project_id : id of the project containing the task
     * @param task_id : id of the task (for an update purpose)
     * @param parent : parent widget
     */
    explicit DialogTask(int project_id, int task_id, QWidget *parent = 0);

    /**
     * @brief highlight search results.
     * @param pattern : the pattern
     */
    void highlightSearch(QString pattern);
    ~DialogTask();

private slots:
    void on_pushButtonCancel_clicked();

    void on_pushButtonOK_clicked();

private:
    Ui::DialogTask *ui;
    Task *m_task;
};

#endif // DIALOGTASK_H
