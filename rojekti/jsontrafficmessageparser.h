#ifndef JSONTRAFFICMESSAGEPARSER_H
#define JSONTRAFFICMESSAGEPARSER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class jsonTrafficMessageParser
{
public:
    /**
     * @brief jsonTrafficMessageParser, constructor.
     * @param file, the json file
     * If the file is unusable
     * it will make the total traffic messages amount -1.
     */
    jsonTrafficMessageParser(const QString file);

    /**
     * @brief getTaskAmountPerDay
     * @return (int) total amount of traffic messages
     * Will return -1 if there was error with the file.
     */
    int getTotalTrafficAmount();
private:
    QJsonDocument jsonFile_;
    QJsonObject jsonObject_;
    QJsonArray features_;
    int messageAmount_;

    /**
     * @brief createJsonObject
     * @return false if object cannot be created
     */
    bool createJsonObject();

    /**
     * @brief getData calculates the total amount.
     */
    void getData();
};

#endif // JSONTRAFFICMESSAGEPARSER_H
