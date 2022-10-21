#include "jsonnetworker.h"
#include <QNetworkAccessManager>



jsonNetworker::jsonNetworker(QObject *parent = nullptr) : QObject(parent)
{
    connect(&manager, &QNetworkAccessManager::sslErrors, this, &jsonNetworker::sslErrors);
}

void jsonNetworker::get(QString location)
{
    //QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    //connect(manager, &QNetworkAccessManager::finished, this, &jsonNetworker::downloadFinished);
}

void jsonNetworker::readyRead()
{

}

void jsonNetworker::finished(QNetworkReply *reply)
{

}


