#include "jsontrafficmessageparser.h"

jsonTrafficMessageParser::jsonTrafficMessageParser(const QString file)
{

}

bool jsonTrafficMessageParser::createJsonObject()
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
