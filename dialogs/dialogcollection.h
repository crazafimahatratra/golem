#ifndef DIALOGCOLLECTION_H
#define DIALOGCOLLECTION_H

#include <QDialog>
#include "models/collection.h"
#include "mainwindow.h"

namespace Ui {
class DialogCollection;
}

class DialogCollection : public QDialog
{
    Q_OBJECT

public:
    explicit DialogCollection(int collection_id, MainWindow *parent = 0);
    ~DialogCollection();

private slots:
    void on_pushButtonOK_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::DialogCollection *ui;
    MainWindow *m_parent;
    Collection *m_collection;
};

#endif // DIALOGCOLLECTION_H
