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
    //std::cout << features_.size() << std::endl;
    wantedValue_ = std::to_string(features_.size());
}
