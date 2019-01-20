#include "dialogtasksnotification.h"
#include "ui_dialogtasksnotification.h"
#include "notificationelement.h"
#include "models/project.h"
#include "constants.h"
#include <QDebug>
#include <QPushButton>
#include <QSound>
#include "bus.h"
#include "mainwindow.h"

DialogTasksNotification::DialogTasksNotification(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogTasksNotification)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint, true);
    connect(Bus::instance(), SIGNAL(taskDeleted(int,int)), this, SLOT(on_taskDeleted(int,int)));
    connect(Bus::instance(), SIGNAL(taskUpdated(int,int,int)), this, SLOT(on_taskUpdated(int,int,int)));
}

DialogTasksNotification::~DialogTasksNotification()
{
    delete ui;
}

void DialogTasksNotification::showTask(Task *task)
{
    if(taskIndex(task->id) < 0)
    {
        this->show();
        NotificationElement *widget = new NotificationElement(this);
        connect(widget, SIGNAL(taskDone(int)), this, SLOT(on_taskDone(int)));
        connect(widget, SIGNAL(taskDetailsRequested(int)), this, SLOT(on_taskDetailsRequested(int)));
        widget->setTask(task);
        ui->stackedWidget->addWidget(widget);
        updateLabelPage();
        this->resetPosition();
        QSound::play(":/others/ding.wav");
    }
    delete task;
}

void DialogTasksNotification::on_pushButtonPrev_clicked()
{
    int i = ui->stackedWidget->currentIndex();
    if(i == 0)
        return;
    ui->stackedWidget->setCurrentIndex(i - 1);
    updateLabelPage();
}

void DialogTasksNotification::on_pushButtonNext_clicked()
{
    int i = ui->stackedWidget->currentIndex();
    if(i >= ui->stackedWidget->count())
        return;
    ui->stackedWidget->setCurrentIndex(i + 1);
    updateLabelPage();
}

void DialogTasksNotification::on_taskDone(int task_id)
{
    int index = taskIndex(task_id);
    if(index < 0)
        return;
    Task *t = Task::findById<Task>(task_id);
    if(t)
    {
        t->status = TASK_STATUS_FINISHED;
        t->update();
        emit Bus::instance()->taskUpdated(t->id, t->project_id, t->project_id);
        ui->stackedWidget->removeWidget(ui->stackedWidget->widget(index));
        updateLabelPage();
        delete t;
    }
    if(ui->stackedWidget->count() == 0)
        this->hide();
}

void DialogTasksNotification::on_taskDetailsRequested(int task_id)
{
    int index = taskIndex(task_id);
    if(index < 0)
        return;
    Task *t = Task::findById<Task>(task_id);
    if(t)
    {
        MainWindow *m = (MainWindow *)this->parent();
        m->openProject(t->project_id);
        delete t;
    }
}

void DialogTasksNotification::on_taskDeleted(int task_id, int)
{
    int index = taskIndex(task_id);
    if(index >= 0)
    {
        ui->stackedWidget->removeWidget(ui->stackedWidget->widget(index));
        updateLabelPage();
    }
}

void DialogTasksNotification::on_taskUpdated(int task_id, int, int)
{
    int index = taskIndex(task_id);
    if(index < 0)
        return;
    NotificationElement *widget = (NotificationElement *) ui->stackedWidget->widget(index);
    if(!widget)
        return;
    Task *t = Task::findById<Task>(task_id);
    if(!t)
        return;
    if(t->status == TASK_STATUS_FINISHED)
    {
        ui->stackedWidget->removeWidget(widget);
        updateLabelPage();
    } else {
        widget->setTask(t);
    }
    delete t;
}

void DialogTasksNotification::resetPosition()
{
    int x = this->parentWidget()->width() + this->parentWidget()->x() - this->width() - 20;
    int y = this->parentWidget()->height() + this->parentWidget()->y() - this->height() - 20;
    this->move(x, y);
}

void DialogTasksNotification::updateLabelPage()
{
    ui->labelPage->setText(QString("%1/%2").arg(ui->stackedWidget->currentIndex() + 1).arg(ui->stackedWidget->count()));
}

int DialogTasksNotification::taskId(int index)
{
    if(index >= ui->stackedWidget->count())
        return 0;
    NotificationElement *widget = (NotificationElement *) ui->stackedWidget->widget(index);
    if(widget)
        return widget->taskId();
    return 0;
}

int DialogTasksNotification::taskIndex(int task_id)
{
    for(int i = 0; i < ui->stackedWidget->count(); i++)
    {
        if(task_id == taskId(i))
            return i;
    }
    return -1;
}
