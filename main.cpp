#include "mainwindow.h"
#include <QApplication>
#include <QFontDatabase>
#include <QDebug>
#include <QLibrary>
#include "appversion.h"
#include "qtkit/QSqliteWrapper/version.h"
#include "qtkit/QSqliteWrapper/backup.h"
#include "models/goption.h"

QByteArray readTextFile(const QString &file_path)
{
    QFile input_file(file_path);
    QByteArray input_data;

    if (input_file.open(QIODevice::Text | QIODevice::Unbuffered | QIODevice::ReadOnly)) {
        input_data = input_file.readAll();
        input_file.close();
        return input_data;
    }
    else {
        return QByteArray();
    }
}

void backup(Goption::BackupSchedule schedule)
{
    Goption *option = Goption::getRow<Goption>();
    if(!option)
        option = new Goption();
    if(schedule != option->backupSchedule)
    {
        delete option;
        return;
    }
    if(!option->backup)
    {
        delete option;
        return;
    }
    if(option->backupPath.isEmpty())
    {
        delete option;
        return;
    }
    QString suffix = "";
    QDateTime d = QDateTime::currentDateTime();
    switch(option->backupFileNaming)
    {
    case Goption::BackupFileNaming::perMinute:
        suffix = d.toString("yyyyMMdd_HHmm");
        break;
    case Goption::BackupFileNaming::hourly:
        suffix = d.toString("yyyyMMdd_HH");
        break;
    case Goption::BackupFileNaming::daily:
        suffix = d.toString("yyyyMMdd");
        break;
    case Goption::BackupFileNaming::weekly:
        suffix = QString("%1_S%2").arg(d.toString("yyyyMM")).arg(d.date().weekNumber());
        break;
    case Goption::BackupFileNaming::monthly:
        suffix = d.toString("yyyyMM");
        break;
    }
    Backup::backup(option->backupPath, suffix);
    delete option;
}

int main(int argc, char *argv[])
{
    int currentExitCode = 0;
    qputenv("QT_BEARER_POLL_TIMEOUT", QByteArray::number(-1));

    QApplication::setApplicationName(APP_NAME);
    QApplication::setApplicationDisplayName(APP_NAME);
    QApplication::setApplicationVersion(APP_VERSION);
    QApplication::setOrganizationName(APP_ORGANIZATION_NAME);
    QApplication::setOrganizationDomain(APP_ORGANIZATION_DOMAIN);
    QSqliteWrapper::DbConnector::useAppData(true);
    QSqliteWrapper::DbConnector::setDbName("golem.db");

    backup(Goption::BackupSchedule::appStart);
    do {
        QApplication a(argc, argv);

        a.setStyleSheet(readTextFile(":/css/styles.css"));
        QFontDatabase::addApplicationFont(":/fonts/fonts/open-sans-v15-latin-regular.ttf");
        QFontDatabase::addApplicationFont(":/fonts/fonts/open-sans-v15-latin-700.ttf");

        QFontDatabase::addApplicationFont(":/fonts/fonts/oswald-v16-latin-regular.ttf");
        QFontDatabase::addApplicationFont(":/fonts/fonts/oswald-v16-latin-700.ttf");

        Version v;
        v.upgrade(":/sql/upgrade.sql");

        MainWindow w;
        w.show();
        currentExitCode = a.exec();
    } while (currentExitCode == MainWindow::EXIT_CODE_REBOOT);
    backup(Goption::BackupSchedule::appClose);
    return currentExitCode;
}
