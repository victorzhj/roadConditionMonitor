#include "jsonroadmaintenanceparser.h"

jsonRoadMaintenanceParser::jsonRoadMaintenanceParser(const QString file, std::string task)
{
    jsonFile_ = QJsonDocument::fromJson(file.toUtf8());
    taskName_ = QString::fromStdString(task);

    bool isObject = createJsonObject();
    if (isObject == false) {
        return;
    }
    getDataPerTask();
}

std::map<dayInt, int> jsonRoadMaintenanceParser::getTaskAmountPerDay()
{
    return taskAmountPerDay;
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

void jsonRoadMaintenanceParser::getDataPerTask()
{
    foreach (auto val, features_) {
        QJsonObject properties = val.toObject();
        QJsonArray tasks = properties.value("tasks").toArray();
        foreach (auto task, tasks) {
            if (task.toString() == taskName_) {
                QString startingTime = properties.value("startTime").toString();
                QString firstSection = startingTime.section('T',0,0);
                QString day = firstSection.section('-',2,2);
                std::map<dayInt, int>::iterator it = taskAmountPerDay.find(day.toInt());
                if (it == taskAmountPerDay.end()) {
                    taskAmountPerDay.insert({day.toInt(), 1});
                } else {
                    it++;
                }
            }
        }
    }
}
