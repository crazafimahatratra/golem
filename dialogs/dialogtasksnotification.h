#ifndef DIALOGTASKSNOTIFICATION_H
#define DIALOGTASKSNOTIFICATION_H

#include <QDialog>
#include "models/task.h"

namespace Ui {
class DialogTasksNotification;
}

class DialogTasksNotification : public QDialog
{
    Q_OBJECT

public:
    explicit DialogTasksNotification(QWidget *parent = 0);
    ~DialogTasksNotification();
    void showTask(Task *task);
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
