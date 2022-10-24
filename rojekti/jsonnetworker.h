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

public slots:
    void get(QString location);



private slots:
    void readyRead();
    void authenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator);
    void encrypted(QNetworkReply *reply);
    void finished(QNetworkReply *reply);
    void preSharedKeyAuthenticationRequired(QNetworkReply *reply, QSslPreSharedKeyAuthenticator *authenticator);
    void proxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator);
    void sslErrors(QNetworkReply *reply, const QList<QSslError> &errors);

private:
    QString startTime;
    QString endTime;
    QString X_MIN;
    QString Y_MIN;
    QString X_MAX;
    QString Y_MAX;

    QNetworkAccessManager manager;
    QString myUrl= "https://tie.digitraffic.fi/api/maintenance/v1/tracking/routes?endFrom=2022-01-19T09%3A00%3A00Z&endBefore=2022-01-19T14%3A00%3A00Z&xMin=21&yMin=61&xMax=22&yMax=62&taskId=&domain=state-roads";

};

#endif // JSONNETWORKER_H
