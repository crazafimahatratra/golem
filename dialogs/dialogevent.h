#ifndef DIALOGEVENT_H
#define DIALOGEVENT_H

#include <QDialog>
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
    explicit DialogEvent(int id, QWidget *parent = 0);

    /**
     * @brief set the selected project
     * @param project_id : id of the project to be selected
     */
    void setSelectedProject(int project_id);

    /**
     * @brief highlight search results.
     * @param pattern : the pattern
     */
    void highlightSearch(QString pattern);
    ~DialogEvent();

private slots:
    void on_pushButtonCancel_clicked();

    void on_pushButtonOK_clicked();

private:
    Ui::DialogEvent *ui;
    Event *m_event;
};

#endif // DIALOGEVENT_H
