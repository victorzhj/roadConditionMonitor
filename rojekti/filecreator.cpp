#include "filecreator.h"
#include "qjsonobject.h"

fileCreator::fileCreator()
{

}

QList<QString> fileCreator::loadGraphNames()
{
    QFile file("graphs.txt");
    if(!file.open(QIODevice::ReadOnly)){
        qCritical() << file.errorString();
        return QList<QString>();
    }
    QByteArray jsonFile_ = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(jsonFile_);
    file.close();
    return doc.object().keys();
}

void fileCreator::writetoGraphs(QJsonObject something)
{
    QFile file("graphs.txt");
    QJsonDocument myDoc(something);
    if(!file.open(QIODevice::WriteOnly )){
        qCritical() << file.errorString();
        return;
    }
    file.write(myDoc.toJson());
    file.close();
}

QJsonObject fileCreator::getGraphsfromfile()
{
    QFile file("graphs.txt");
    if(!file.open(QIODevice::ReadOnly)){
        qCritical() << file.errorString();
        return QJsonObject();
    }
   QByteArray jsonFile_ = file.readAll();
   file.close();
   QJsonDocument tempdoc = QJsonDocument::fromJson(jsonFile_);
   return tempdoc.object();
}
