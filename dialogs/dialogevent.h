#ifndef DIALOGEVENT_H
#define DIALOGEVENT_H

#include <QDialog>
#include "mainwindow.h"
#include "models/event.h"

namespace Ui {
class DialogEvent;
}

class DialogEvent : public QDialog
{
    Q_OBJECT

public:
    explicit DialogEvent(int id, MainWindow *parent = 0);
    void setSelectedProject(int project_id);
    ~DialogEvent();

private slots:
    void on_pushButtonCancel_clicked();

    void on_pushButtonOK_clicked();

private:
    Ui::DialogEvent *ui;
    MainWindow *m_parent;
    Event *m_event;
};

#endif // DIALOGEVENT_H
