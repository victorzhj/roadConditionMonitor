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
// puuttuu vielä yksi
static const QMap<placeName, QVector<minMaxXY>> locations = {{"Pori E8", {"21.7536", "61.4837", "21.7537", "61.4838"}},
                                                                      {"Tampere 65", {"23.6587", "61.5160", "23.6588", "61.5161"}},
                                                                      {"Hämeenlinna E12", {"24.4670", "60.9826", "24.4671", "60.9827"}},
                                                                      {"Pasila Pasilankatu", {"24.9262", "60.2020", "24.9263", "60.2021"}}};

class model
{
public:

    QList<QPoint> pointdata2_;
    model();
    QList<QPoint> getChart();
    int getPreferences();
    void updateChart(std::vector<int> timeData, std::vector<int> OtherData);
    void updatePreferences();
    void setTimeRange(QDateTime start, QDateTime end);
    void getRoadMaintenance(const QDateTime start, const QDateTime end, const  QString taskName, const QString location);
    void getRoadCondition(const std::string item, const std::string forecastTime, QString location);
    void getTrafficMsg();
    void getXmlWeatherObservation(const QString time, const QString param, const QString location);
    void getXmlAvgMinMaxTemp(const QString time, const QDateTime start, const QDateTime end, const QString param, const QString location);
    void getXmlWeatherForecast(const QDateTime startTime, QString duration, const QString param, const QString location);
    void jsonGetData(QString whatData, QString where);

private:
    QList<QPoint> pointdata_;
    //using int as placeholder type since not sure what it will be
    int preferences_;
    jsonNetworker* networker_ = new jsonNetworker();
    QDateTime start_;
    QDateTime end_;

    QMap<QString,QVector<QString>> coordMap;
    urlBuilder urlBuilder;
};

#endif // MODEL_H
