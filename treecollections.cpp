#include "treecollections.h"
#include "constants.h"
#include <QDebug>

TreeCollections::TreeCollections(QWidget *parent) : QTreeWidget(parent)
{
    this->setAcceptDrops(true);
}

bool TreeCollections::dropMimeData(QTreeWidgetItem *parent, int index, const QMimeData *data, Qt::DropAction action)
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
    if(parent->type() != TREEVIEW_TYPE_PROJECT)
        return false;
    int project_id = parent->data(0, Qt::UserRole).toInt();
    if(id)
        emit this->taskDroped(id, project_id);
    return false;
}
