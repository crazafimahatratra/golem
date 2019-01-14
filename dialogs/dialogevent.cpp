#include "dialogevent.h"
#include "ui_dialogevent.h"

DialogEvent::DialogEvent(MainWindow *parent) :
    QDialog(parent),
    ui(new Ui::DialogEvent),
    m_parent(parent)
{
    ui->setupUi(this);
}

DialogEvent::~DialogEvent()
{
    delete ui;
}
