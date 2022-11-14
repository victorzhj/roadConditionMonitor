#include "xmlparser.h"

static const std::string Time = "time";

xmlParser::xmlParser(const QString file)
{
    if(!file_.setContent(file))
        {
            // TODO
            return;
        }
    file_.setContent(file);
    parse();
}

std::map<parameter, std::vector<value> > xmlParser::getValues()
{
    return storedData_;
}

int xmlParser::getAmount() {
    return amount_;
}

void xmlParser::parse()
{
    std::set<std::string> storeTimeValues;
    QDomNodeList timeList = file_.elementsByTagName("BsWfs:Time");
    QDomNodeList parameterNameList = file_.elementsByTagName("BsWfs:ParameterName");
    QDomNodeList parameterValueList = file_.elementsByTagName("BsWfs:ParameterValue");
    QDomNodeList coordList = file_.elementsByTagName("gml:pos");
    QString coord = file_.elementsByTagName("gml:pos").at(0).toElement().text();

    // QString helloWorld=list1.at(0).toElement().text();
    for (auto i = 0; i < timeList.size(); i++) {
        if (!(coordList.at(i).toElement().text().toStdString() == coord.toStdString())) {
            continue;
        }
        std::string tempTime = timeList.at(i).toElement().text().toStdString();
        std::string tempParameterName = parameterNameList.at(i).toElement().text().toStdString();
        std::string tempParameterValue = parameterValueList.at(i).toElement().text().toStdString();
        if (!(acceptedParameters.count(tempParameterName) != 0)) {
            continue;
        }
        if (storeTimeValues.count(tempTime) == 0) {
            // std::cout << "TEST" << std::endl;
            storedData_[Time].push_back(tempTime);
            storeTimeValues.insert(tempTime);
        }
        storedData_[acceptedParameters.at(tempParameterName)].push_back(tempParameterValue);
    }
    amount_ = timeList.size();

    for (auto &i : storedData_) {
        std::cout << i.first << std::endl;
        std::cout << i.second.size() << std::endl;;
        for (auto &j : i.second) {
            std::cout << j << std::endl;
        }

    }


}



