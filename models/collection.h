#ifndef COLLECTION_H
#define COLLECTION_H
#include "qtkit/QSqliteWrapper/table.h"

/**
 * @brief Represents a collection in database
 */
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

    /**
     * @brief id of the collection
     */
    int id;

    /**
     * @brief name of the collection
     */
    QString name;
};

#endif // COLLECTION_H
