#ifndef BUS_H
#define BUS_H

#include <QObject>
#include <QDateTime>

/**
 * @brief This is a bus-like class because it transports every signals used in this project.
 * It should be used as a singleton pattern.
 */
class Bus : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Constructor
     * @param parent : the caller parent
     */
    explicit Bus(QObject *parent = nullptr);

    /**
     * @brief Returns the single instanciated Bus
     * @return
     */
    static Bus* instance();

signals:
    /**
     * @brief raised when a project gets updated.
     * @param project_id : id of the project Project::id
     */
    void projectUpdated(int project_id);

    /**
     * @brief raised when a project has been deleted.
     * @param project_id : id of the project Project::id
     */
    void projectDeleted(int project_id);

    /**
     * @brief when a collection has been updated or inserted
     * @param collection_id : id of the collection
     */
    void collectionUpdated(int collection_id);

    /**
     * @brief when a collection has been deleted
     * @param collection_id : id of the collection
     */
    void collectionDeleted(int collection_id);

    /**
     * @brief when a task has been updated or deleted
     * @param task_id : id of the task
     * @param project_id : id of the project
     * @param old_project_id : id of the previous project (if changed)
     */
    void taskUpdated(int task_id, int project_id, int old_project_id);

    /**
     * @brief when a task has been deleted
     * @param task_id : id of the task
     * @param project_id : id of the project
     */
    void taskDeleted(int task_id, int project_id);

    /**
     * @brief when an event have been updated or created
     * @param event_id : id of the event
     * @param project_id : id of the project
     * @param date : event date
     * @param old_project_id : id of the previous project (if changed)
     * @param old_date : this holds the previous date if it was changed
     */
    void eventUpdated(int event_id, int project_id, QDateTime date, int old_project_id, QDateTime old_date);

    /**
     * @brief when an event has been deleted
     * @param event_id : id of the event
     * @param project_id : id of the project
     * @param date : event date
     */
    void eventDeleted(int event_id, int project_id, QDateTime date);
public slots:

private:
    static Bus* _instance;
};

#endif // BUS_H
