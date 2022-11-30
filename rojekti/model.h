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
#include "jsonnetworker.h"
#include "xmlparser.h"

#include <QMap>
#include <QList>

#include "jsonnetworker.h"
#include "urlbuilder.h"

using coord = QString;
using minMaxXY = QString;
using placeName = QString;


// vector where data is stored [minX, minY, maxX, maxY]
static const QMap<placeName, QVector<minMaxXY>> locations = {
    {"Valtatie 12 Kauppi", {"23.8165", "61.5034", "23.8166", "61.5035"}},
    {"E8 Pori", {"21.7536", "61.4837", "21.7537", "61.4838"}},
    {"Tie 65 Lielahti", {"23.6587", "61.5160", "23.6588", "61.5161"}},
    {"E12 Virveli Hämeenlinna", {"24.4670", "60.9826", "24.4671", "60.9827"}},
    {"Pasilankatu Helsinki", {"24.9262", "60.2020", "24.9263", "60.2021"}}
    };

class model
{
public:

    QList<QPointF> pointdata2_;
    model();
    QList<QPointF> getChart();
    void updateChart(std::vector<double> timeData, std::vector<double> OtherData);
    void getRoadMaintenance(const QDateTime start, const QDateTime end, const  QString taskName, const QString location);
    void getRoadCondition(const std::string item, const std::string forecastTime, QString location);
    void getTrafficMsg();
    void getXmlWeatherObservation(const QString param, const QString location);
    void getXmlAvgMinMaxTemp(const QDateTime start, const QDateTime end, const QString param, const QString location);
    void getXmlWeatherForecast(const QDateTime startTime, const QString param, const QString location);
    void getXmlDataHelper(const QString xml, const QString param);

private:
    QList<QPointF> pointdata_;
    jsonNetworker* networker_ = new jsonNetworker();
    QDateTime start_;
    QDateTime end_;

    QMap<QString,QVector<QString>> coordMap;
    urlBuilder urlBuilder;
};

#endif // MODEL_H
