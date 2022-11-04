#include "jsonnetworker.h"
#include "qeventloop.h"
#include <QNetworkAccessManager>
#include <QtGlobal>


jsonNetworker::jsonNetworker(QObject *parent) : QObject(parent)
{}


QString jsonNetworker::getUrl(QUrl url)
{
    QNetworkAccessManager *man = new QNetworkAccessManager(this);
    QNetworkReply *reply = man->get(QNetworkRequest(QUrl(url)));
    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    QString answer = reply->readAll();
    return answer;
}


