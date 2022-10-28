#include "jsonroadmaintenanceparser.h"

jsonRoadMaintenanceParser::jsonRoadMaintenanceParser(const QString file):
jsonFile_(QJsonDocument::fromJson(file.toUtf8()))
{
    jsonFile_ = QJsonDocument::fromJson(file.toUtf8());

    bool isObject = createJsonObject();
    if (isObject == false) {
        taskAmount = -1;
    } else {
        getData();
    }
}


bool jsonRoadMaintenanceParser::createJsonObject()
{
    if (jsonFile_.isEmpty()) {
        return false;
    } else if (jsonFile_.isArray()) {
        return false;
    } else if (jsonFile_.isObject()) {
        jsonObject_ = jsonFile_.object();
        if (!jsonObject_.value("features").isUndefined()) {
            features_ = jsonObject_.value("features").toArray();
            return true;
        }
    }
    return false;
}


void jsonRoadMaintenanceParser::getData()
{
    taskAmount = features_.size();
}


int jsonRoadMaintenanceParser::getTaskAmountPerDay()
{
    return taskAmount;
}
