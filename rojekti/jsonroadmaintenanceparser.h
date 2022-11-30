#ifndef JSONROADMAINTENANCEPARSER_H
#define JSONROADMAINTENANCEPARSER_H

#include "ijsonparser.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <iostream>
#include <map>

using maintenanceType = std::string;

class jsonRoadMaintenanceParser: public IjsonParser
{
public:
    /**
     * @brief jsonRoadMaintenanceParser, constructor.
     * @param file, the json file
     * If the file is unusable
     * it will make the total amount -1.
     */
    jsonRoadMaintenanceParser(const QString file);

private:

    /**
     * @brief getData calculates the total amount.
     */
    virtual void getData() override;

};

#endif // JSONROADMAINTENANCEPARSER_H
