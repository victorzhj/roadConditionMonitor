#include "filecreator.h"
#include "qjsonobject.h"
#include "qpixmap.h"
#include <QDir>
#include <filesystem>
#include <iostream>
#include <sstream>
fileCreator::fileCreator()
{

}

QList<QString> fileCreator::loadGraphNames()
{
    QFile file("graphs.txt");
    file.open(QIODevice::ReadOnly);
    QByteArray jsonFile_ = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(jsonFile_);
    file.close();
    return getImageNames(doc.object().keys());
}

void fileCreator::writetoGraphs(QJsonObject something, int i)
{
    QFile file("graphs.txt");
    if(i == 1) {
        file.setFileName("preferences.txt");
    }

    QJsonDocument myDoc(something);
    file.open(QIODevice::WriteOnly);
    file.write(myDoc.toJson());
    file.close();
}

QJsonObject fileCreator::getGraphsfromfile(int i)
{
    QFile file("graphs.txt");
    if(i == 1) {
        file.setFileName("preferences.txt");
    }

    file.open(QIODevice::ReadOnly);
   QByteArray jsonFile_ = file.readAll();
   file.close();
   QJsonDocument tempdoc = QJsonDocument::fromJson(jsonFile_);
   return tempdoc.object();
}

QList<QString> fileCreator::getImageNames(QList<QString> stuff) {

    std::filesystem::create_directory("graphImages");
    std::filesystem::path dir = std::filesystem::current_path().append("graphImages");
   for (const auto & entry : std::filesystem::directory_iterator(dir))
         {QDir directory = QDir(QString::fromStdString(entry.path().string()));
       QString imagename = directory.dirName();
       imagename.remove(imagename.size()-4, 4);
       stuff.append(imagename);}

   return stuff;
}
