#include "networker.h"
#include "qeventloop.h"
#include <QNetworkAccessManager>
#include <QtGlobal>


Networker::Networker(QObject *parent) : QObject(parent) {

}


QString Networker::getData(QUrl url) {
    QNetworkAccessManager *man = new QNetworkAccessManager(this);
    QNetworkReply *reply = man->get(QNetworkRequest(QUrl(url)));
    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    QString answer = reply->readAll();
    return answer;
}


