#ifndef UPDATEMANAGER_H
#define UPDATEMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QSslError>

/**
 * @brief Checks for update online and then raises a signal if there is any.
 */
class UpdateManager : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Constructor
     * @param parent : parent widget
     */
    explicit UpdateManager(QObject *parent = nullptr);
    ~UpdateManager();

    /**
     * @brief Checks for the latest version online and raises the signal versionFetched() if any
     * @param local_version : the version of the running program
     * @param url : url of the online ressource
     * The online ressource should returns a json of the following format :
     * \code
     {
    "release_date": "2019-01-17 14:52:38",
    "version": "1.0.0.1"
     }
     * \endcode
     */
    void check(QString local_version, QString url);

signals:
    /**
     * @brief raised when the version was fetched successfully
     * @param newer : true if the online version is newer than the current running version
     * @param version : the online version fetched
     */
    void versionFetched(bool newer, QString version);

    /**
     * @brief raised when an error occured during the fetch
     * @param error : the error encountered
     */
    void versionFetchError(QString error);

public slots:
    /**
     * @brief called by the m_manager when the fetch is complete
     * @param reply : the network reply
     */
    void onFinished(QNetworkReply *reply);
private:
    QNetworkAccessManager *m_manager;
    QString m_localversion;
};

#endif // UPDATEMANAGER_H
