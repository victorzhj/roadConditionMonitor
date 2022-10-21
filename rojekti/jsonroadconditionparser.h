#ifndef JSONROADCONDITIONPARSER_H
#define JSONROADCONDITIONPARSER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <iostream>
#include <map>

class jsonRoadConditionParser
{
public:
    /**
     * @brief jsonRoadConditionParser, constructor
     * @param file, the json file
     * @param item, the wanted item (overallRoadCondition, precipitationCondition)
     * @param forecastTime
     * Parses the file with road conditions
     */
    jsonRoadConditionParser(const QString file, const std::string item, const std::string forecastTime);

    /**
     * @brief getWantedValue
     * @return the wanted value
     */
    std::string getWantedValue();

private:
    QJsonDocument jsonFile_;
    QJsonObject jsonObject_;
    QJsonArray weatherDatas_;

    QString item_;
    QString forecastTime_;

    std::string wantedValue_;

    /**
     * @brief createJsonObject
     * @return false if object cannot be created
     */
    bool createJsonObject();

    /**
     * @brief getData, get the wanted value
     */
    void getData();
};

#endif // JSONROADCONDITIONPARSER_H
