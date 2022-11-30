#include "ijsonparser.h"


std::string IjsonParser::getValue()
{
    return wantedValue_;
}

bool IjsonParser::createJsonObject(QString param)
{
    if (jsonFile_.isEmpty()) {
        return false;
    } else if (jsonFile_.isArray()) {
        return false;
    } else if (jsonFile_.isObject()) {
        jsonObject_ = jsonFile_.object();
        if (!jsonObject_.value(param).isUndefined()) {
            features_ = jsonObject_.value(param).toArray();
            return true;
        }
    }
    return false;
}
