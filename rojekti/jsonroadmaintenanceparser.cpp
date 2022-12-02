#include "jsonroadmaintenanceparser.h"

jsonRoadMaintenanceParser::jsonRoadMaintenanceParser(const QString file) {
    jsonFile_ = QJsonDocument::fromJson(file.toUtf8());

    bool isObject = createJsonObject("features");
    if (isObject == false) {
        wantedValue_ = "-1";
    } else {
        jsonRoadMaintenanceParser::getData();
    }
}

void jsonRoadMaintenanceParser::getData() {
    wantedValue_ = std::to_string(features_.size());
}
