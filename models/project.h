#ifndef PROJECT_H
#define PROJECT_H
#include "qtkit/QSqliteWrapper/table.h"

/**
 * @brief Represents a project from the table project in database
 */
class Project : public QSqliteWrapper::Table
{
public:
    Project();

    // Table interface
public:
    QString pkName() { return "id"; }
    QVariant pkValue() { return this->id; }
    void setPkValue(QVariant value) { this->id = value.toInt(); }
    void fromRecord(QSqlRecord record)
    {
        this->id = record.value("id").toInt();
        this->collection_id = record.value("collection_id").toInt();
        this->name = record.value("name").toString();
        this->color = record.value("color").toString();
    }
    QList<QSqliteWrapper::Parameter> prepareParameters()
    {
        QList<QSqliteWrapper::Parameter> parameters;
        parameters.append(QSqliteWrapper::Parameter("collection_id", this->collection_id));
        parameters.append(QSqliteWrapper::Parameter("name", this->name));
        parameters.append(QSqliteWrapper::Parameter("color", this->color));
        return parameters;
    }

    /**
     * @brief id of the project
     */
    int id;

    /**
     * @brief id of the collection containing the project
     * @see Collection::id
     */
    int collection_id;

    /**
     * @brief name of the project
     */
    QString name;

    /**
     * @brief color of the project icon
     */
    QString color;
};

#endif // PROJECT_H
