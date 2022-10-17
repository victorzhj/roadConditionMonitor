#ifndef JSONROADMAINTENANCEPARSER_H
#define JSONROADMAINTENANCEPARSER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <iostream>
#include <map>

using dayInt = int;
using hour = int;
using minute = int;
using maintenanceType = std::string;

class jsonRoadMaintenanceParser
{
public:
    jsonRoadMaintenanceParser(const QString file, std::string task = "null");

    std::map<dayInt, int> getTaskAmountPerDay();
private:
    QString taskName_;
    QJsonDocument jsonFile_;
    QJsonObject jsonObject_;
    QJsonArray features_;
    std::map<dayInt, int> taskAmountPerDay;

    bool createJsonObject();
    void getDataPerTask();

};

#endif // JSONROADMAINTENANCEPARSER_H
