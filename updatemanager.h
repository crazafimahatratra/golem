#ifndef UPDATEMANAGER_H
#define UPDATEMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QSslError>
#include <QThread>
#include "models/history.h"

/**
 * @brief Checks for update online and then raises a signal if there is any.
 */
class UpdateManager : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Constructor
     * @param version : current version of the local application
     * @param url : Url of the online ressource
     * @param parent : parent widget
     *
     * The online ressource should be of the below format :
     * @code
     *
     {
        "release_date": "2019-01-17 14:52:38",
        "version": "1.0.0.1"
     }
     * @endcode
     */
    explicit UpdateManager(QString version, QString url, QObject *parent = nullptr);
    ~UpdateManager();

    /**
     * @brief Starts fetching the current version.
     * It is called so to be conform with QThread::start().
     */
    void start();

signals:
    /**
     * @brief when fetching is started.
     */
    void fetchStarted();
    /**
     * @brief raised when the version was fetched successfully.
     * @param newer : true if the online version is newer than the current running version.
     * @param version : the online version fetched.
     */
    void versionFetched(bool newer, QString version);

    /**
     * @brief raised when an error occured during the fetch.
     * @param error : the error encountered
     */
    void versionFetchError(QString error);

public slots:
    /**
     * @brief called by the m_manager when the fetch is complete.
     * @param reply : the network reply.
     */
    void onFinished(QNetworkReply *reply);

    /**
     * @brief onActualStart : the checks for update is actually starting.
     */
    void onActualStart();
private:
    QNetworkAccessManager *m_manager;
    QString m_localversion;
    QString m_url;
    History *m_history;
    bool canUpdate();
};

#endif // UPDATEMANAGER_H
