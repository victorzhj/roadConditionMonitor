#ifndef FILECREATOR_H
#define FILECREATOR_H
#include <QFile>
#include <QString>
#include <QJsonArray>
#include <QJsonDocument>
#include <QList>

class fileCreator
{
public:
    QString path_;
    fileCreator();
    QList<QString> loadNames(int i = 0) ;
    void writetoFiles(QJsonObject something, int whichfile = 0);
    QJsonObject getGraphsfromfile(int whichfile = 0);

    QList<QString> getImageNames(QList<QString> stuff);
};

#endif // FILECREATOR_H
