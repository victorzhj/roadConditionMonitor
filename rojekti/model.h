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

#include "jsonnetworker.h"


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
    void jsonGetData();
private:
    QList<QPoint> pointdata_;
    //using int as placeholder type since not sure what it will be
    int preferences_;
    jsonNetworker* networker_ = new jsonNetworker();
    QDateTime start_;
    QDateTime end_;
};

#endif // MODEL_H
