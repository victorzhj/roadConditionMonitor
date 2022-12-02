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

//Gets the graph names from the files or preference names from preferences.txt
QList<QString> fileCreator::loadNames(int i) {
    QByteArray jsonFile_;
    QJsonDocument doc;
    QFile file("graphs.txt");
    if(i == 1) {
        file.setFileName("preferences.txt");
    }
    if(QFileInfo::exists(file.fileName())){file.open(QIODevice::ReadOnly);
        jsonFile_ = file.readAll();
        doc = QJsonDocument::fromJson(jsonFile_);
        file.close();
    }

    if(i == 1) {
        return doc.object().keys();
    } else {
    return getImageNames(doc.object().keys());
    }
}

//Writes the content to a file specified by i
void fileCreator::writetoFiles(QJsonObject something, int i) {
    QFile file("graphs.txt");
    if(i == 1) {
        file.setFileName("preferences.txt");
    }

    QJsonDocument myDoc(something);
    file.open(QIODevice::WriteOnly);
    file.write(myDoc.toJson());
    file.close();
}

//Gets the content from a while specified by i
QJsonObject fileCreator::getGraphsfromfile(int i) {
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

//Gets the names of the images in graphImages folder
QList<QString> fileCreator::getImageNames(QList<QString> stuff) {
    std::filesystem::create_directory("graphImages");
    std::filesystem::path dir = std::filesystem::current_path().append("graphImages");
    for (const auto & entry : std::filesystem::directory_iterator(dir)) {
       QDir directory = QDir(QString::fromStdString(entry.path().string()));
       QString imagename = directory.dirName();
       imagename.remove(imagename.size()-4, 4);
       stuff.append(imagename);
    }

   return stuff;
}
