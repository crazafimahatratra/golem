#ifndef BACKUPMANAGER_H
#define BACKUPMANAGER_H

#include <QObject>

class BackupManager : public QObject
{
    Q_OBJECT
public:
    explicit BackupManager(QObject *parent = nullptr);

signals:

public slots:
};

#endif // BACKUPMANAGER_H