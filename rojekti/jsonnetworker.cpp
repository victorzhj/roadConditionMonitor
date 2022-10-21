#include "jsonnetworker.h"
#include <QNetworkAccessManager>



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
    qInfo () << "Getting from server...";
    QNetworkReply* reply = manager.get(QNetworkRequest(QUrl(location)));
    connect(reply, &QNetworkReply::readyRead,this,&jsonNetworker::readyRead);
    //QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    //connect(manager, &QNetworkAccessManager::finished, this, &jsonNetworker::downloadFinished);
}

void jsonNetworker::readyRead()
{

}

void jsonNetworker::authenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator)
{

}

void jsonNetworker::encrypted(QNetworkReply *reply)
{

}

void jsonNetworker::finished(QNetworkReply *reply)
{

}

void jsonNetworker::preSharedKeyAuthenticationRequired(QNetworkReply *reply, QSslPreSharedKeyAuthenticator *authenticator)
{

}

void jsonNetworker::proxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator)
{

}

void jsonNetworker::sslErrors(QNetworkReply *reply, const QList<QSslError> &errors)
{

}


