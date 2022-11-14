#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <QDomDocument>
#include <QObject>
#include <map>
#include <set>
#include <iostream>

using parameter = std::string;
using value = std::string;
static const std::map<std::string, std::string> acceptedParameters = {{"t2m", "oTemp"},
                                                                      {"ws_10min", "oWindSeed"},
                                                                      {"n_man", "oCloudiness"},
                                                                      {"temperature", "fTemp"},
                                                                      {"windspeedms", "fWindSpeed"},
                                                                      {"TA_PT1H_AVG", "avgTemp"},
                                                                      {"TA_PT1H_MAX", "maxTemp"},
                                                                      {"TA_PT1H_MIN", "minTemp"}};

class xmlParser
{
public:
    xmlParser(const QString file);
private:
    void parse();

    std::map<std::string, std::vector<value>> storedData_;
    QDomDocument file_;

};

#endif // XMLPARSER_H
