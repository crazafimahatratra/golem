#ifndef TABLEEVENTS_H
#define TABLEEVENTS_H

#include <QWidget>
#include <QTableWidget>
#include <QMimeData>
#include <QDropEvent>

class TableEvents : public QTableWidget
{
    Q_OBJECT
public:
    explicit TableEvents(QWidget *parent = nullptr);

signals:
    void taskReceived(int id);

public slots:

    // QTableWidget interface
protected:
    bool dropMimeData(int, int, const QMimeData *data, Qt::DropAction);
};

#endif // TABLEEVENTS_H
