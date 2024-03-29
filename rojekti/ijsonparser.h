#ifndef IJSONPARSER_H
#define IJSONPARSER_H
#include <QJsonDocument>
#include <iostream>
#include <QJsonObject>
#include <QJsonArray>

// Interface for json data parsing.
class IjsonParser
{
public:
    /**
     * @brief get the wanted value
     * @return (string) the wanted value
     * Will return (string) -1 if there was error with the file.
     */
    std::string getValue();
protected:

    QJsonDocument jsonFile_;
    QJsonObject jsonObject_;
    std::string wantedValue_;
    QJsonArray features_;

    /**
     * @brief createJsonObject
     * @return false if object cannot be created
     */
    bool createJsonObject(QString param);

    /**
     * @brief getData, get the wanted value
     */
    virtual void getData() = 0;
};

#endif // IJSONPARSER_H
