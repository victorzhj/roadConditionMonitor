#ifndef MODEL_H
#define MODEL_H

#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QString>
#include <QJsonArray>
#include <QJsonDocument>
#include <QList>
#include <QPoint>
#include <iostream>

#include "jsonroadmaintenanceparser.h"
#include "jsonroadconditionparser.h"
#include "jsontrafficmessageparser.h"
#include "networker.h"
#include "xmlparser.h"

#include <QMap>
#include <QList>

#include "networker.h"
#include "urlbuilder.h"

using coord = QString;
using minMaxXY = QString;
using placeName = QString;


// vector where data is stored [minX, minY, maxX, maxY]
static const QMap<placeName, QVector<minMaxXY>> locations = {
    {"Valtatie 12 Kauppi", {"23.7400", "61.4600", "23.8000", "61.5200"}},
    {"E8 Pori", {"21.7800", "61.4700", "21.7900", "61.4800"}},
    {"E12 Pirkkala", {"23.5000", "61.4000", "23.6500", "61.5000"}},
    {"E12 Virveli Hämeenlinna", {"24.4000", "60.9000", "24.5000", "61.0000"}},
    {"Tie 45 Helsinki", {"24.9400", "60.1700", "24.9500", "60.2200"}}
    };

class model
{
public:

    /**
     * @brief pointdata for the lower chart
     */
    QList<QPointF> pointdata2_;
    /**
     * @brief default constructor
     */
    model();

    /**
     * @brief getChart
     * @return the points in the upper chart
     */
    QList<QPointF> getChart();

    /**
     * @brief updateChart Changes the pointdata
     * @param timeData for the x-axis
     * @param OtherData for the y-axis
     */
    void updateChart(std::vector<double> timeData, std::vector<double> OtherData);
    /**
     * @brief getRoadMaintenance gets road mainenance data
     * @param QDateTime start, start time
     * @param QDateTime end, end time
     * @param QString taskName, the name of the task
     * @param QString location
     */
    void getRoadMaintenance(const QDateTime start, const QDateTime end, const  QString taskName, const QString location);
    /**
     * @brief getRoadCondition, gets road maintenance data
     * @param std::string item
     * @param std::string forecastTime
     * @param QString location
     * @return std::string either the precipitation amount or the overallroadcondition
     */
    std::string getRoadCondition(const std::string item, const std::string forecastTime, QString location);
    /**
     * @brief getTrafficMsg, gets traffic message data
     * @return std::string the amount of traffic messages
     */
    std::string getTrafficMsg(std::string messageType);

    /**
     * @brief getXmlWeatherObservation, gets data for observation temp, ws and cloudiness
     * @param QString param, the data that is wanted (t2m, ws_10min, n_man)
     * @param QString location, the location
     */
    void getXmlWeatherObservation(const QString param, const QString location);
    /**
     * @brief getXmlAvgMinMaxTemp, gets data for avg, min and max temp
     * @param QDateTime start, start time
     * @param QDateTime end, end time
     * @param QString param, the data that is wanted (TA_PT1H_AVG, TA_PT1H_MAX, TA_PT1H_MIN)
     * @param QString location, the location
     */
    void getXmlAvgMinMaxTemp(const QDateTime start, const QDateTime end, const QString param, const QString location);
    /**
     * @brief getXmlWeatherForecast, gets data for forecast temp and ws
     * @param QDateTime startTime, start time
     * @param QString param, the data that is wanted (temperature, windspeedms)
     * @param QString location, the location
     */
    void getXmlWeatherForecast(const QDateTime startTime, const QString param, const QString location);


private:
    QList<QPointF> pointdata_;
    Networker* networker_ = new Networker();
    QDateTime start_;
    QDateTime end_;

    urlBuilder urlBuilder;

    /**
     * @brief getXmlDataHelper
     * @param QString xml, the xml file
     * @param QString param, the wanted values
     */
    void getXmlDataHelper(const QString xml, const QString param);
};

#endif // MODEL_H
