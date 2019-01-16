#ifndef DIALOGEVENT_H
#define DIALOGEVENT_H

#include <QDialog>
#include "mainwindow.h"
#include "models/event.h"

namespace Ui {
class DialogEvent;
}

/**
 * @brief Dialog for creating or editing an event
 */
class DialogEvent : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     * @param id : id of the event (for editing purpose)
     * @param parent widget
     */
    explicit DialogEvent(int id, MainWindow *parent = 0);

    /**
     * @brief set the selected project
     * @param project_id : id of the project to be selected
     */
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
