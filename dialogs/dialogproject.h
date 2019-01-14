#ifndef DIALOGPROJECT_H
#define DIALOGPROJECT_H

#include <QDialog>
#include "models/project.h"
#include "mainwindow.h"

namespace Ui {
class DialogProject;
}

class DialogProject : public QDialog
{
    Q_OBJECT

public:
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
