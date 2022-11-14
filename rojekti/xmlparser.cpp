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
    QDomNodeList timeList = file_.elementsByTagName("BsWfs:Time");
    QDomNodeList parameterNameList = file_.elementsByTagName("BsWfs:ParameterName");
    QDomNodeList parameterValueList = file_.elementsByTagName("BsWfs:ParameterValue");
    // QString helloWorld=list1.at(0).toElement().text();
    for (auto i = 0; i < timeList.size(); i++) {
        std::string tempTime = timeList.at(i).toElement().text().toStdString();
        std::string tempParameterName = parameterNameList.at(i).toElement().text().toStdString();
        std::string tempParameterValue = parameterValueList.at(i).toElement().text().toStdString();
        storedData_[Time].push_back(tempTime);
        if (acceptedParameters.count(tempParameterName) != 0) {
            storedData_[acceptedParameters.at(tempParameterName)].push_back(tempParameterValue);
        }
    }
    amount_ = timeList.size();

    for (auto i : storedData_) {
        std::cout << i.first << std::endl;
        for (auto j : i.second) {
            std::cout << j << std::endl;
        }
    }

}

