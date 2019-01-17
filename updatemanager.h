#ifndef UPDATEMANAGER_H
#define UPDATEMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QSslError>


class UpdateManager : public QObject
{
    Q_OBJECT
public:
    explicit UpdateManager(QObject *parent = nullptr);
    ~UpdateManager();
    void check(QString local_version, QString url);

signals:
    void versionFetched(bool newer, QString version);
    void versionFetchError(QString error);

public slots:
    void onFinished(QNetworkReply *reply);
private:
    QNetworkAccessManager *m_manager;
    QString m_localversion;
};

#endif // UPDATEMANAGER_H
