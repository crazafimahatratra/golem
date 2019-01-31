#ifndef GOPTION_H
#define GOPTION_H
#include "qtkit/QSqliteWrapper/table.h"

using namespace QSqliteWrapper;

/**
 * @brief The Goption class is a representation of the goption table
 */
class Goption : public Table
{
public:
    Goption();

    // Table interface
public:
    /**
     * @brief Enumeration of update schedule.
     */
    enum class UpdateSchedule
    {
        appStart = 1,   ///< Checks for an update everytime the app starts.
        daily = 2,      ///< Checks for an update every day.
        weekly = 3,     ///< Checks for an update every monday (week).
        monthly = 4     ///< Checks for an update every 1st of the month.
    };

    /**
     * @brief Enumeration for the backup schedule.
     */
    enum class BackupSchedule
    {
        appStart = 1,   ///< Every time the app starts.
        appClose = 2    ///< Every time the app is about to close.
    };

    /**
     * @brief The BackupFileNaming enum enumerates the pattern of the file used for backups.
     */
    enum class BackupFileNaming
    {
        perMinute = 1,  ///< yyyyMMdd_HHmm
        hourly = 2,     ///< yyyyMMdd_HH
        daily = 3,      ///< yyyyMMdd
        weekly = 4,     ///< yyyyMMdd_SX
        monthly = 5     ///< yyyyMM
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

    /**
     * @brief id : primary key.
     */
    int id;

    /**
     * @brief checkUpdate : whether checks for update is active or not.
     */
    bool checkUpdate;

    /**
     * @brief updateSchedule : when should the app checks for an update.
     */
    UpdateSchedule updateSchedule;

    /**
     * @brief backup : if the app should trigger a backup or not.
     */
    bool backup;

    /**
     * @brief backupSchedule : when the backup should be triggered.
     */
    BackupSchedule backupSchedule;

    /**
     * @brief backupFileNaming : pattern of the backup filename
     */
    BackupFileNaming backupFileNaming;

    /**
     * @brief backupPath : path of the automatic update
     */
    QString backupPath;
};

#endif // GOPTION_H
