#include "updatemanager.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVersionNumber>
#include <QNetworkConfiguration>

UpdateManager::UpdateManager(QString version, QString url, QObject *parent) :
    QObject(parent),
    m_manager(new QNetworkAccessManager(this)),
    m_localversion(version),
    m_url(url)
{
    connect(m_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onFinished(QNetworkReply*)));
}

UpdateManager::~UpdateManager()
{
    qDebug() << "Destructor";
    delete m_manager;
}

void UpdateManager::start()
{
    qDebug() << "Open " << m_url;
    qDebug() << m_manager->configuration().connectTimeout();
    m_manager->get(QNetworkRequest(QUrl(m_url)));
    qDebug() << "Wait fetching ...";
    emit this->fetchStarted();
}

void UpdateManager::onFinished(QNetworkReply *reply)
{
    qDebug() << "reply";
    if (reply->error()) {
        emit this->versionFetchError(reply->errorString());
        return;
    }
    QByteArray ans = reply->readAll();
    QJsonDocument document;
    document.fromJson(ans);
    QJsonObject obj = document.fromJson(ans).object();
    if(obj.contains("version"))
    {
        QVersionNumber distant = QVersionNumber::fromString(obj["version"].toString());
        QVersionNumber local = QVersionNumber::fromString(m_localversion);
        int res = QVersionNumber::compare(distant, local);
        if(res > 0)
        {
            emit this->versionFetched(true, distant.toString());
        } else {
            emit this->versionFetched(false, distant.toString());
        }
    }
}

