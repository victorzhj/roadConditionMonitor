#include "jsonroadconditionparser.h"

jsonRoadConditionParser::jsonRoadConditionParser(const QString file, const std::string item, const std::string forecastTime):
item_(QString::fromStdString(item)), forecastTime_(QString::fromStdString(forecastTime))
{
    forecastTime_ = forecastTime_ + "h";
    jsonFile_ = QJsonDocument::fromJson(file.toUtf8());
    bool isObject = createJsonObject("weatherData");
    if (isObject == false) {
        wantedValue_ = "noValue";
    } else {
        jsonRoadConditionParser::getData();
    }
}

void jsonRoadConditionParser::getData()
{
    if (features_.size() == 0) {
        wantedValue_ = "noValue";
        return;
    }
    QJsonObject weatherData = features_.at(0).toObject();
    QJsonArray roadConditions = weatherData.value("roadConditions").toArray();
    foreach (const QJsonValue jsonValue, roadConditions) {
        QJsonObject tempObject = jsonValue.toObject();
        std::string test = tempObject.value("forecastName").toString().toStdString();
        if (test == forecastTime_.toStdString()) {
            if (item_ == "overallRoadCondition") {
                wantedValue_ = tempObject.value("overallRoadCondition").toString().toStdString();
            } else {
                QJsonObject forecastConditionReason = tempObject.value("forecastConditionReason").toObject();
                wantedValue_ = forecastConditionReason.value(item_).toString().toStdString();
            }
        }
    }
}
