#ifndef HISTORY_H
#define HISTORY_H
#include "qtkit/QSqliteWrapper/table.h"
#include <QDateTime>

using namespace QSqliteWrapper;
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

    static History *currentHistory();

    int id;
    QDateTime checkUpdate;
};

#endif // HISTORY_H
