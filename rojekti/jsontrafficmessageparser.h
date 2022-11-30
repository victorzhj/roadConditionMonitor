#ifndef JSONTRAFFICMESSAGEPARSER_H
#define JSONTRAFFICMESSAGEPARSER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "ijsonparser.h"

class jsonTrafficMessageParser: public IjsonParser
{
public:
    /**
     * @brief jsonTrafficMessageParser, constructor.
     * @param file, the json file
     * If the file is unusable
     * it will make the total traffic messages amount -1.
     */
    jsonTrafficMessageParser(const QString file);

private:

    /**
     * @brief getData calculates the total amount.
     */
    virtual void getData() override;
};

#endif // JSONTRAFFICMESSAGEPARSER_H
