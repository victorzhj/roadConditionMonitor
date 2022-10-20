#include "jsonroadmaintenanceparser.h"

jsonRoadMaintenanceParser::jsonRoadMaintenanceParser(const QString file, std::string task)
{
    jsonFile_ = QJsonDocument::fromJson(file.toUtf8());
    taskName_ = QString::fromStdString(task);

    bool isObject = createJsonObject();
    if (isObject == false) {
        return;
    }
    getData();
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
