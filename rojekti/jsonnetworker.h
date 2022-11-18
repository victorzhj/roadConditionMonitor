#ifndef JSONNETWORKER_H
#define JSONNETWORKER_H

#include <QNetworkReply>
#include <QString>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QString>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QAuthenticator>
#include <iostream>
#include <QDebug>

#include <QJsonValue>
#include <QJsonObject>

class jsonNetworker : public QObject
{
public:
    explicit jsonNetworker(QObject *parent = nullptr);

    QString getUrl(QUrl url);

private:
    QNetworkAccessManager manager;
    QString myUrl= "https://tie.digitraffic.fi/api/maintenance/v1/tracking/routes?endFrom=2022-01-19T09%3A00%3A00Z&endBefore=2022-01-19T14%3A00%3A00Z&xMin=21&yMin=61&xMax=22&yMax=62&taskId=&domain=state-roads";

};

#endif // JSONNETWORKER_H
