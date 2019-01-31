#ifndef HISTORY_H
#define HISTORY_H
#include "qtkit/QSqliteWrapper/table.h"
#include <QDateTime>

using namespace QSqliteWrapper;

/**
 * @brief Represents the history table. It holds the informations about the last update.
 */
class History : public Table
{
public:
    History();

    // Table interface
public:
    QString pkName()
    {
        return "id";
    }
    QVariant pkValue()
    {
        return id;
    }
    void setPkValue(QVariant value)
    {
        id = value.toInt();
    }
    void fromRecord(QSqlRecord record)
    {
        id = record.value("id").toInt();
        checkUpdate = record.value("checkupdate").toDateTime();
    }
    QList<Parameter> prepareParameters()
    {
        QList<Parameter> parameters;
        parameters.append(Parameter("checkupdate", checkUpdate));
        return parameters;
    }

    /**
     * @brief gets the current history if any, or returns a default History object.
     * @return
     */
    static History *currentHistory();

    /**
     * @brief id : primary key.
     */
    int id;

    /**
     * @brief checkUpdate : the last time the application checks for an update.
     */
    QDateTime checkUpdate;
};

#endif // HISTORY_H
