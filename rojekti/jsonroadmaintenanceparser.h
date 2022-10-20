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
    jsonRoadMaintenanceParser(const QString file, std::string task = "null");

    int getTaskAmountPerDay();
private:
    QString taskName_;
    QJsonDocument jsonFile_;
    QJsonObject jsonObject_;
    QJsonArray features_;
    int taskAmount;

    bool createJsonObject();
    void getData();

};

#endif // JSONROADMAINTENANCEPARSER_H
