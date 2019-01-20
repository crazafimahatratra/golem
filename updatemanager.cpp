#include "updatemanager.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVersionNumber>

UpdateManager::UpdateManager(QObject *parent) :
    QObject(parent),
    m_manager(new QNetworkAccessManager(parent))
{
    connect(m_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onFinished(QNetworkReply*)));
}

UpdateManager::~UpdateManager()
{
    qDebug() << "Destructor";
    delete m_manager;
}

void UpdateManager::check(QString local_version, QString url)
{
    qDebug() << "Open " << url;
    m_localversion = local_version;
    m_manager->get(QNetworkRequest(QUrl(url)));
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
