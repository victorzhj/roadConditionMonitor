#ifndef JSONROADCONDITIONPARSER_H
#define JSONROADCONDITIONPARSER_H

#include "ijsonparser.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <iostream>
#include <map>

class jsonRoadConditionParser: public IjsonParser
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

private:
    QString item_;
    QString forecastTime_;

    /**
     * @brief getData, get the wanted value
     */
    virtual void getData() override;
};

#endif // JSONROADCONDITIONPARSER_H
