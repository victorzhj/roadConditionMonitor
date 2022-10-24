#include "jsonroadconditionparser.h"

jsonRoadConditionParser::jsonRoadConditionParser(const QString file, const std::string item, const std::string forecastTime)
{
    item_ = QString::fromStdString(item);
    forecastTime_ = QString::fromStdString(forecastTime);
    jsonFile_ = QJsonDocument::fromJson(file.toUtf8());

    bool isObject = createJsonObject();
    if (isObject == false) {
        wantedValue_ = "noValue";
    } else {
        getData();
    }
}

std::string jsonRoadConditionParser::getWantedValue()
{
    return wantedValue_;
}


bool jsonRoadConditionParser::createJsonObject()
{
    if (jsonFile_.isEmpty()) {
        return false;
    } else if (jsonFile_.isArray()) {
        return false;
    } else if (jsonFile_.isObject()) {
        jsonObject_ = jsonFile_.object();
        if (!jsonObject_.value("weatherData").isUndefined()) {
            weatherDatas_ = jsonObject_.value("features").toArray();
            return true;
        }
    }
    return false;
}

void jsonRoadConditionParser::getData()
{
    if (weatherDatas_.size() == 0) {
        wantedValue_ = "noValue";
        return;
    }
    QJsonObject weatherData = weatherDatas_.at(0).toObject();

    QJsonArray roadConditions = weatherData.value("roadConditions").toArray();
    foreach (const QJsonValue jsonValue, roadConditions) {
        QJsonObject tempObject = jsonValue.toObject();
        if (tempObject.value("forecastName").toString() == forecastTime_) {
            if (forecastTime_ == "0") {
                wantedValue_ = tempObject.value("overallRoadCondition").toString().toStdString();
            } else {
                wantedValue_ = tempObject.value(item_).toString().toStdString();
            }
        }
    }
}
