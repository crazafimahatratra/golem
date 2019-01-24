#-------------------------------------------------
#
# Project created by QtCreator 2019-01-10T11:28:52
#
#-------------------------------------------------

QT       += core gui sql network multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Golem
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    qtkit/QSqliteWrapper/dbconnector.cpp \
    qtkit/QSqliteWrapper/join.cpp \
    qtkit/QSqliteWrapper/parameter.cpp \
    qtkit/QSqliteWrapper/table.cpp \
    qtkit/QSqliteWrapper/version.cpp \
    dialogs/dialogcollection.cpp \
    models/collection.cpp \
    dialogs/dialogproject.cpp \
    models/project.cpp \
    mdi/mdiproject.cpp \
    dialogs/dialogtask.cpp \
    models/task.cpp \
    dialogs/dialogevent.cpp \
    models/event.cpp \
    mdi/mdievents.cpp \
    qtkit/WidgetUtils/tablewidget.cpp \
    qtkit/WidgetUtils/treewidget.cpp \
    qtkit/QSqliteWrapper/backup.cpp \
    dialogs/dialogabout.cpp \
    updatemanager.cpp \
    notifierthread.cpp \
    dialogs/dialogtasksnotification.cpp \
    dialogs/notificationelement.cpp \
    bus.cpp \
    qtkit/WidgetUtils/rtfeditor.cpp \
    qtkit/WidgetUtils/texteditor.cpp

HEADERS += \
        mainwindow.h \
    qtkit/QSqliteWrapper/dbconnector.h \
    qtkit/QSqliteWrapper/join.h \
    qtkit/QSqliteWrapper/parameter.h \
    qtkit/QSqliteWrapper/table.h \
    qtkit/QSqliteWrapper/version.h \
    appversion.h \
    dialogs/dialogcollection.h \
    models/collection.h \
    dialogs/dialogproject.h \
    models/project.h \
    mdi/mdiproject.h \
    dialogs/dialogtask.h \
    models/task.h \
    constants.h \
    dialogs/dialogevent.h \
    models/event.h \
    mdi/mdievents.h \
    qtkit/WidgetUtils/tablewidget.h \
    qtkit/WidgetUtils/treewidget.h \
    qtkit/QSqliteWrapper/backup.h \
    dialogs/dialogabout.h \
    updatemanager.h \
    notifierthread.h \
    dialogs/dialogtasksnotification.h \
    dialogs/notificationelement.h \
    bus.h \
    qtkit/WidgetUtils/rtfeditor.h \
    qtkit/WidgetUtils/texteditor.h

FORMS += \
        mainwindow.ui \
    dialogs/dialogcollection.ui \
    dialogs/dialogproject.ui \
    mdi/mdiproject.ui \
    dialogs/dialogtask.ui \
    dialogs/dialogevent.ui \
    mdi/mdievents.ui \
    dialogs/dialogabout.ui \
    dialogs/dialogtasksnotification.ui \
    dialogs/notificationelement.ui \
    qtkit/WidgetUtils/rtfeditor.ui

RC_FILE = resources.rc

DISTFILES += \
    resources.rc \
    upgrade.sql \
    styles.css

RESOURCES += \
    icons.qrc \
    files.qrc \
    qtkit/WidgetUtils/qtkiticons.qrc
