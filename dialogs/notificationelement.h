#ifndef NOTIFICATIONELEMENT_H
#define NOTIFICATIONELEMENT_H

#include <QWidget>
#include "models/task.h"
#include "models/project.h"

namespace Ui {
class NotificationElement;
}

class NotificationElement : public QWidget
{
    Q_OBJECT

public:
    explicit NotificationElement(QWidget *parent = 0);
    ~NotificationElement();
    void setTask(Task *task);
    int taskId();

signals:
    void taskDone(int task_id);
    void taskDetailsRequested(int task_id);

private slots:
    void on_pushButtonDone_clicked();

    void on_pushButtonGo_clicked();

private:
    Ui::NotificationElement *ui;
    int m_taskid;
};

#endif // NOTIFICATIONELEMENT_H
