#include "updatemanager.h"
#include "models/goption.h"
#include "models/history.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVersionNumber>
#include <QNetworkConfiguration>
#include <QTimer>
#include <QThread>

UpdateManager::UpdateManager(QString version, QString url, QObject *parent) :
    QObject(parent),
    m_manager(new QNetworkAccessManager(this)),
    m_localversion(version),
    m_url(url)
{
    m_history = History::currentHistory();
    connect(m_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onFinished(QNetworkReply*)));
}

UpdateManager::~UpdateManager()
{
    qDebug() << "Destructor";
    delete m_manager;
    delete m_history;
}

void UpdateManager::start()
{
    qDebug() << "UpdateManager::start";
    if(canUpdate())
    {
        qDebug() << "Can update";
        onActualStart();
    }
    else
    {
        qDebug() << "Cannot update";
    }
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
        m_history->checkUpdate = QDateTime::currentDateTime();
        if(m_history->id == 0)
            m_history->insert();
        else
            m_history->update();
        if(res > 0)
        {
            emit this->versionFetched(true, distant.toString());
        } else {
            emit this->versionFetched(false, distant.toString());
        }
    }
}

void UpdateManager::onActualStart()
{
    m_manager->get(QNetworkRequest(QUrl(m_url)));
    qDebug() << "Wait fetching ...";
    emit this->fetchStarted();
}

bool UpdateManager::canUpdate()
{
    qDebug() << "Check if I can update";
    Goption *option = Goption::getRow<Goption>();
    if(!option)
        option = new Goption();
    QDate today = QDate::currentDate();
    QDate last = m_history->checkUpdate.date();
    if(!option->checkUpdate)
    {
        qDebug() << "Update disabled";
        return false;
    }
    if(option->updateSchedule == Goption::UpdateSchedule::appStart)
    {
        qDebug() << "Update on each start";
        return true;
    }
    if(!last.isValid())
    {
        qDebug() << "Never been updated";
        return true;
    }
    if(option->updateSchedule == Goption::UpdateSchedule::daily)
    {
        qDebug() << "Update daily" << last;
        return (last < today);
    }
    if(option->updateSchedule == Goption::UpdateSchedule::weekly)
    {
        qDebug() << "Update weekly" << last;
        return (last < today && today.day() == 1);
    }
    if(option->updateSchedule == Goption::UpdateSchedule::monthly)
    {
        qDebug() << "Update monthly" << last;
        return (last < today && today.month() == 1);
    }
    return false;
}


