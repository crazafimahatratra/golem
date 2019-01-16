#ifndef DIALOGPROJECT_H
#define DIALOGPROJECT_H

#include <QDialog>
#include "models/project.h"
#include "mainwindow.h"

namespace Ui {
class DialogProject;
}

/**
 * @brief Dialog for creating or editing a project
 */
class DialogProject : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     * @param collection_id : id of the collection containing the project
     * @param project_id : id of the project (for an update purpose)
     * @param parent : parent widget
     */
    explicit DialogProject(int collection_id, int project_id, MainWindow *parent = 0);
    ~DialogProject();

private slots:
    void on_pushButtonOK_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::DialogProject *ui;
    MainWindow *m_parent;
    Project *m_project = nullptr;
};

#endif // DIALOGPROJECT_H
