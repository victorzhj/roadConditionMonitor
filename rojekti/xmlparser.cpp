#include "xmlparser.h"

xmlParser::xmlParser(const QString file, const QString param):
    param_(param)
{
    if(!file_.setContent(file))
        {
            return;
        }
    file_.setContent(file);
    parse();
}

std::vector<value> xmlParser::getValues() {
    return storedData_;
}

std::vector<dateTime> xmlParser::getTimes() {
    return times_;
}

int xmlParser::getAmount() {
    return amount_;
}

void xmlParser::parse() {
    std::set<std::string> storeTimeValues;
    QDomNodeList timeList = file_.elementsByTagName("BsWfs:Time");
    QDomNodeList parameterNameList = file_.elementsByTagName("BsWfs:ParameterName");
    QDomNodeList parameterValueList = file_.elementsByTagName("BsWfs:ParameterValue");
    QDomNodeList coordList = file_.elementsByTagName("gml:pos");
    QString coord = file_.elementsByTagName("gml:pos").at(0).toElement().text();

    // QString helloWorld=list1.at(0).toElement().text();
    for (auto i = 0; i < timeList.size(); i++) {
        // Check if coords are right
        if (!(coordList.at(i).toElement().text().toStdString() == coord.toStdString())) {
            continue;
        }
        std::string tempTime = timeList.at(i).toElement().text().toStdString();
        QString tempParameterName = parameterNameList.at(i).toElement().text();
        std::string tempParameterValue = parameterValueList.at(i).toElement().text().toStdString();
        // Check if param in file is right
        if (param_ != tempParameterName) {
            continue;
        }
        if (tempParameterValue == "NaN") {
            continue;
        }
        // Add time to set for checking duplicate times
        if (storeTimeValues.count(tempTime) == 0) {
            times_.push_back(tempTime);
            storeTimeValues.insert(tempTime);
        }
        // Store the value
        storedData_.push_back(tempParameterValue);
    }
    amount_ = timeList.size();
}



