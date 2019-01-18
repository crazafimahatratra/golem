#ifndef NOTIFIERTHREAD_H
#define NOTIFIERTHREAD_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include "models/task.h"

class NotifierThread : public QObject
{
    Q_OBJECT
public:
    explicit NotifierThread(QObject *parent = nullptr);
    ~NotifierThread();
    void start();

signals:
    void taskDueDateReached(Task *task);

public slots:
    void onTimeout();

private:
    QTimer *m_timer;
};

#endif // NOTIFIERTHREAD_H
