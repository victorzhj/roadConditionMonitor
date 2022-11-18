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
    void writetoGraphs(QJsonObject something);
    QJsonObject getGraphsfromfile();
};

#endif // FILECREATOR_H
