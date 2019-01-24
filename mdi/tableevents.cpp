#include "tableevents.h"
#include <QDebug>

TableEvents::TableEvents(QWidget *parent) : QTableWidget(parent)
{

}

bool TableEvents::dropMimeData(int, int, const QMimeData *data, Qt::DropAction)
{
    QByteArray encoded = data->data(data->formats()[0]);
    QDataStream stream(&encoded, QIODevice::ReadOnly);
    int id = 0;
    while (!stream.atEnd())
    {
        int row, col;
        QMap<int,  QVariant> roleDataMap;
        stream >> row >> col >> roleDataMap;

        /* do something with the data */
        if(col != 0)
            continue;
        if(!roleDataMap.contains(Qt::UserRole))
            continue;
        id = roleDataMap[Qt::UserRole].toInt();
    }
    if(id)
        emit this->taskReceived(id);
    return false;
}
