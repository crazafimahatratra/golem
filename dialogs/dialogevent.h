#ifndef DIALOGEVENT_H
#define DIALOGEVENT_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class DialogEvent;
}

class DialogEvent : public QDialog
{
    Q_OBJECT

public:
    explicit DialogEvent(MainWindow *parent = 0);
    ~DialogEvent();

private:
    Ui::DialogEvent *ui;
    MainWindow *m_parent;
};

#endif // DIALOGEVENT_H
