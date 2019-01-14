#ifndef DIALOGTASK_H
#define DIALOGTASK_H

#include <QDialog>
#include "mainwindow.h"
#include "models/project.h"
#include "models/task.h"

namespace Ui {
class DialogTask;
}

class DialogTask : public QDialog
{
    Q_OBJECT

public:
    explicit DialogTask(int project_id, int task_id, MainWindow *parent = 0);
    ~DialogTask();

private slots:
    void on_pushButtonCancel_clicked();

    void on_pushButtonOK_clicked();

private:
    Ui::DialogTask *ui;
    MainWindow *m_parent;
    Task *m_task;
};

#endif // DIALOGTASK_H
