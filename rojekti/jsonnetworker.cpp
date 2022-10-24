#include "jsonnetworker.h"
#include <QNetworkAccessManager>
#include <QtGlobal>


jsonNetworker::jsonNetworker(QObject *parent) : QObject(parent)
{
    connect(&manager, &QNetworkAccessManager::authenticationRequired, this, &jsonNetworker::authenticationRequired);
    connect(&manager, &QNetworkAccessManager::encrypted, this, &jsonNetworker::encrypted);
    connect(&manager, &QNetworkAccessManager::preSharedKeyAuthenticationRequired, this, &jsonNetworker::preSharedKeyAuthenticationRequired);
    connect(&manager, &QNetworkAccessManager::proxyAuthenticationRequired, this, &jsonNetworker::proxyAuthenticationRequired);
    connect(&manager, &QNetworkAccessManager::sslErrors, this, &jsonNetworker::sslErrors);
}

void jsonNetworker::get(QString location)
{
    //qInfo () << "Getting from server...";
    QNetworkReply* reply = manager.get(QNetworkRequest(QUrl(location)));
    connect(reply, &QNetworkReply::finished,this,&jsonNetworker::finished);
    //QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    //connect(manager, &QNetworkAccessManager::finished, this, &jsonNetworker::downloadFinished);
}

void jsonNetworker::readyRead()
{
    qInfo () << "readyRead";
}

void jsonNetworker::authenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator)
{
    Q_UNUSED(reply);
    Q_UNUSED(authenticator);
    qInfo () << "authenticationRequired";
}

void jsonNetworker::encrypted(QNetworkReply *reply)
{
    Q_UNUSED(reply);
    qInfo () << "encrypted";
}

void jsonNetworker::finished(QNetworkReply *reply)
{
    QString string = reply->readAll();
    QJsonDocument document = QJsonDocument::fromJson(string.toUtf8());

}

void jsonNetworker::preSharedKeyAuthenticationRequired(QNetworkReply *reply, QSslPreSharedKeyAuthenticator *authenticator)
{
    Q_UNUSED(reply);
    Q_UNUSED(authenticator);
    qInfo () << "preSharedKeyAuthenticationRequired";
}

void jsonNetworker::proxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator)
{
    Q_UNUSED(proxy);
    Q_UNUSED(authenticator);
    qInfo () << "proxyAuthenticationRequired";
}

void jsonNetworker::sslErrors(QNetworkReply *reply, const QList<QSslError> &errors)
{
    Q_UNUSED(reply);
    Q_UNUSED(errors);
    qInfo () << "sslErrors";
}


