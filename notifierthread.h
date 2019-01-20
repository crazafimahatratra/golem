#ifndef NOTIFIERTHREAD_H
#define NOTIFIERTHREAD_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include "models/task.h"

/**
 * @brief The NotifierThread class is used to check the tasks that are not completed yet, and then raises the signal taskDueDateReached
 * for each task found
 */
class NotifierThread : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Constructor
     * @param parent : the calling parent
     */
    explicit NotifierThread(QObject *parent = nullptr);
    ~NotifierThread();

    /**
     * @brief starts the NotifierThread instance
     */
    void start();

signals:
    /**
     * @brief raised when the due date of an uncompleted task is reached
     * @param task : the concerned task
     */
    void taskDueDateReached(Task *task);

public slots:
    /**
     * @brief used by the timer m_timer
     */
    void onTimeout();

private:
    QTimer *m_timer;
};

#endif // NOTIFIERTHREAD_H
