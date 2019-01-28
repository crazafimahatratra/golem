#ifndef GOPTION_H
#define GOPTION_H
#include "qtkit/QSqliteWrapper/table.h"

using namespace QSqliteWrapper;
class Goption : public Table
{
public:
    Goption();

    // Table interface
public:
    enum class UpdateSchedule
    {
        appStart = 1,
        daily = 2,
        weekly = 3,
        monthly = 4
    };

    enum class BackupSchedule
    {
        appStart = 1,
        appClose = 2
    };

    enum class BackupFileNaming
    {
        perMinute = 1,
        hourly = 2,
        daily = 3,
        weekly = 4,
        monthly = 5
    };

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
        this->id = record.value("id").toInt();
        this->checkUpdate = record.value("check_update").toBool();
        this->updateSchedule = static_cast<UpdateSchedule>(record.value("update_schedule").toInt());
        this->backup = record.value("backup").toBool();
        this->backupSchedule = static_cast<BackupSchedule>(record.value("backup_schedule").toInt());
        this->backupFileNaming = static_cast<BackupFileNaming>(record.value("backup_filenaming").toInt());
        this->backupPath = record.value("backup_path").toString();
    }
    QList<Parameter> prepareParameters()
    {
        QList<Parameter> params;
        params.append(Parameter("check_update", checkUpdate));
        params.append(Parameter("update_schedule", static_cast<int>(updateSchedule)));
        params.append(Parameter("backup", backup));
        params.append(Parameter("backup_schedule", static_cast<int>(backupSchedule)));
        params.append(Parameter("backup_filenaming", static_cast<int>(backupFileNaming)));
        params.append(Parameter("backup_path", backupPath));
        return params;
    }

    int id;
    bool checkUpdate;
    UpdateSchedule updateSchedule;
    bool backup;
    BackupSchedule backupSchedule;
    BackupFileNaming backupFileNaming;
    QString backupPath;
};

#endif // GOPTION_H
