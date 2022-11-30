#include "jsontrafficmessageparser.h"

jsonTrafficMessageParser::jsonTrafficMessageParser(const QString file)
{
    jsonFile_ = QJsonDocument::fromJson(file.toUtf8());

    bool isObject = createJsonObject("features");
    if (isObject == false) {
        wantedValue_ = "-1";
    } else {
        jsonTrafficMessageParser::getData();
    }
}

void jsonTrafficMessageParser::getData()
{
    wantedValue_ = features_.size();
}
