#ifndef NETWORKER_H
#define NETWORKER_H

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

class Networker : public QObject
{
public:
    /**
     * @brief default constructor
     * @param parent
     */
    explicit Networker(QObject *parent = nullptr);

    /**
     * @brief get content with a network request from the wanted API
     * @param url built in urlBuilder
     * @return QString of requested content
     */
    QString getData(QUrl url);

private:
    /**
     * @brief manager sends network requests and receives replies
     */
    QNetworkAccessManager manager;

};

#endif // NETWORKER_H
