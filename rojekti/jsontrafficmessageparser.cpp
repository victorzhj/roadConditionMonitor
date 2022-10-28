#include "jsontrafficmessageparser.h"

jsonTrafficMessageParser::jsonTrafficMessageParser(const QString file):
jsonFile_(QJsonDocument::fromJson(file.toUtf8()))
{


    bool isObject = createJsonObject();
    if (isObject == false) {
        messageAmount_ = -1;
    } else {
        getData();
    }
}

int jsonTrafficMessageParser::getTotalTrafficAmount()
{
    return messageAmount_;
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

void jsonTrafficMessageParser::getData()
{
    messageAmount_ = features_.size();
}
