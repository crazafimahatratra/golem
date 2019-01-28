#include "goption.h"

Goption::Goption():Table("goption")
{
    id = 0;
    checkUpdate = true;
    updateSchedule = UpdateSchedule::weekly;
    backup = false;
    backupSchedule = BackupSchedule::appClose;
    backupFileNaming = BackupFileNaming::perMinute;
    backupPath = "";
}
