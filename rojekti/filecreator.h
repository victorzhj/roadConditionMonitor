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
    fileCreator();
    QList<QString> loadGraphNames() ;
    void writetoGraphs(QJsonObject something, int whichfile = 0);
    QJsonObject getGraphsfromfile(int whichfile = 0);

};

#endif // FILECREATOR_H
