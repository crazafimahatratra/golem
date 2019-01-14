#ifndef COLLECTION_H
#define COLLECTION_H
#include "qtkit/QSqliteWrapper/table.h"

class Collection: public QSqliteWrapper::Table
{
public:
    Collection();

    // Table interface
public:
    QString pkName()
    {
        return "id";
    }
    QVariant pkValue()
    {
        return this->id;
    }
    void setPkValue(QVariant value)
    {
        this->id = value.toInt();
    }
    void fromRecord(QSqlRecord record)
    {
        this->id = record.value("id").toInt();
        this->name = record.value("name").toString();
    }

    QList<QSqliteWrapper::Parameter> prepareParameters()
    {
        QList<QSqliteWrapper::Parameter> params;
        params.append(QSqliteWrapper::Parameter("name", this->name));
        return params;
    }

    int id;
    QString name;
};

#endif // COLLECTION_H
