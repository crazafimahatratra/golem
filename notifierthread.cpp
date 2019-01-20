#include "notifierthread.h"
#include <QDebug>
#include <QDateTime>
#include "constants.h"

NotifierThread::NotifierThread(QObject *parent) :
    QObject(parent),
    m_timer(new QTimer(parent))
{
    connect(m_timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
}

NotifierThread::~NotifierThread()
{
    qDebug() << "finished";
    delete m_timer;
}

void NotifierThread::start()
{
    m_timer->start(5000);
}

void NotifierThread::onTimeout()
{
    qDebug() << "Check reached tasks " << QDateTime::currentDateTime();
    Task *model = new Task();
    model->where("duedate <=", QDateTime::currentDateTime())
            ->where("status = ", TASK_STATUS_STARTED)
            ->order("duedate");
    QList<Task *> tasks = model->get<Task>();
    for(int i = 0; i < tasks.length(); i++)
    {
        emit this->taskDueDateReached(tasks[i]);
    }
    delete model;
}
