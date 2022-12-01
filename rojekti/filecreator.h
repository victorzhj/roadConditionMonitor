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
    /**
     * @brief The file path
     */
    QString path_;
    /**
     * @brief default constructor
     */
    fileCreator();
    /**
     * @brief Loads graph/preference names from files
     * @param i determines which one we are retrieving
     * @return Qlist<QString> of the names
     */
    QList<QString> loadNames(int i = 0) ;
    /**
     * @brief Writes the parameter something to a file
     * @param something is going to be written in the file
     * @param whichfile tells us if we are saving into graphs.txt or preferences.txt
     */
    void writetoFiles(QJsonObject something, int whichfile = 0);
    /**
     * @brief Returns either the graphs as a QJsonObject or the preferences
     * @param whichfile determines which one we are retrieving
     * @return preferences or graphs as QJsonObject
     */
    QJsonObject getGraphsfromfile(int whichfile = 0);

    /**
     * @brief gets the imagenames from graphImages folder and appends them to the parameter
     * @param stuff
     * @return QList<QString> of stuff + graphImagenames
     */
    QList<QString> getImageNames(QList<QString> stuff);
};

#endif // FILECREATOR_H
