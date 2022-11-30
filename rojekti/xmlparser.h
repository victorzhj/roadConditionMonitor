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
    /**
     * @brief xmlParser, constructor
     * @param file, the file that needs to be read.
     * @param param, the wanted paramater from file
     * Parses xml file with given parameter.
     */
    xmlParser(const QString file, const QString param);
    /**
     * @brief getValues, get the wanted data
     * @return std::vector<std::string> where element is the wanted value
     */
    std::vector<value> getValues();
    /**
     * @brief getTimes, get each values time.
     * @return std::vector<std::string> where element is the time
     */
    std::vector<dateTime> getTimes();
    /**
     * @brief getAmount, returns the total amount of values
     * @return int
     */
    int getAmount();
private:
    /**
     * @brief parse, parses the json data and stores it
     */
    void parse();
    std::vector<value> storedData_;
    std::vector<dateTime> times_;
    QDomDocument file_;
    int amount_;
    QString param_;
};

#endif // XMLPARSER_H
