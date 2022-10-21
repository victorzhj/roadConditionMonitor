#ifndef JSONROADMAINTENANCEPARSER_H
#define JSONROADMAINTENANCEPARSER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <iostream>
#include <map>

using maintenanceType = std::string;

class jsonRoadMaintenanceParser
{
public:
    /**
     * @brief jsonRoadMaintenanceParser, constructor.
     * @param file, the json file
     * If the file is unusable
     * it will make the total amount -1.
     */
    jsonRoadMaintenanceParser(const QString file);

    /**
     * @brief getTaskAmountPerDay
     * @return (int) total amount of certain task
     * Will return -1 if there was error with the file.
     */
    int getTaskAmountPerDay();
private:
    QString taskName_;
    QJsonDocument jsonFile_;
    QJsonObject jsonObject_;
    QJsonArray features_;

    int taskAmount;
    /**
     * @brief createJsonObject
     * @return false if object cannot be created
     */
    bool createJsonObject();

    /**
     * @brief getData calculates the total amount.
     */
    void getData();

};

#endif // JSONROADMAINTENANCEPARSER_H
