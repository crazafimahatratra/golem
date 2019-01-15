#include "mainwindow.h"
#include <QApplication>
#include <QFontDatabase>
#include "appversion.h"
#include "qtkit/QSqliteWrapper/version.h"

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

int main(int argc, char *argv[])
{
    int currentExitCode = 0;
    do {
        QApplication::setApplicationName(APP_NAME);
        QApplication::setApplicationDisplayName(APP_NAME);
        QApplication::setApplicationVersion(APP_VERSION);
        QApplication::setOrganizationName(APP_ORGANIZATION_NAME);
        QApplication::setOrganizationDomain(APP_ORGANIZATION_DOMAIN);
        QApplication a(argc, argv);

        a.setStyleSheet(readTextFile(":/css/styles.css"));
        QFontDatabase::addApplicationFont(":/fonts/fonts/open-sans-v15-latin-regular.ttf");
        QFontDatabase::addApplicationFont(":/fonts/fonts/open-sans-v15-latin-700.ttf");

        QFontDatabase::addApplicationFont(":/fonts/fonts/oswald-v16-latin-regular.ttf");
        QFontDatabase::addApplicationFont(":/fonts/fonts/oswald-v16-latin-700.ttf");

        QSqliteWrapper::DbConnector::useAppData(true);
        QSqliteWrapper::DbConnector::setDbName("golem.db");
        Version v;
        v.upgrade(":/sql/upgrade.sql");

        MainWindow w;
        w.show();
        currentExitCode = a.exec();
    } while (currentExitCode == MainWindow::EXIT_CODE_REBOOT);

    return currentExitCode;
}
