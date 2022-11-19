#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <QDomDocument>
#include <QObject>
#include <map>
#include <set>
#include <iostream>
#include <set>

using parameter = std::string;
using value = std::string;
using dateTime = std::string;

class xmlParser
{
public:
    xmlParser(const QString file, const QString param);
    std::vector<value> getValues();

    int getAmount();
private:
    void parse();
    // std::map<parameter, std::vector<value>> storedData_;
    std::vector<value> storedData_;
    std::vector<dateTime> times_;
    QDomDocument file_;
    int amount_;
    QString param_;
};

#endif // XMLPARSER_H
