#include "model.h"
#include "jsonroadmaintenanceparser.h"
#include "jsonroadconditionparser.h"
#include "jsontrafficmessageparser.h"
#include "xmlparser.h"
#include "creategraph.cpp"
#include <string>
#include <sstream>

model::model()
{
    coordMap["sijainti1"] = {"61.516", "23.658", "61.517", "23.659"};
}

QList<QPoint> model::getChart() {
    //returns the points on the chart
    return pointdata_;
}

int model::getPreferences()
{
    return preferences_;
}

void model::updateChart(vector<int> timeData, vector<int> OtherData) {
    //Combines two vectors into chart points (QPoint)
    pointdata_.clear();
    for (int i = 0; i < std::min(timeData.size(), OtherData.size()); ++i)
        {
            pointdata_.append(QPoint(timeData[i], OtherData[i]));
        }
}

void model::updatePreferences()
{

}

void model::setTimeRange(QDateTime start, QDateTime end)
{
    // TODO keksi parempi tapa antaa aikaleimat
    start_ = start;
    end_ = end;
}

void model::jsonGetData(QString whatData, QString where)
{
    vector<int> xaxis = {};
    vector<int> yaxis = {};
    int days = start_.daysTo(end_);

    // get min and max coordinates
    QList<QString> coords = coordMap[where];


    // tämä for loop on todella hidas kun on useampia päiviä. (useat HTTP kutsut on hitaita)
    for (int i = 0; i <= days; i++) {
        QDateTime current = start_.addDays(i);
        stringstream t;
        std::string dateString = current.date().toString(Qt::ISODate).toStdString();
        t<< "https://tie.digitraffic.fi/api/maintenance/v1/tracking/routes?endFrom=" << dateString << "T09%3A00%3A00Z&endBefore=" << dateString << "T14%3A00%3A00Z&xMin=21&yMin=61&xMax=22&yMax=62&taskId=&domain=state-roads";
        QString string = QString::fromStdString(t.str());
        QString json = networker_->getUrl(QUrl(string));
        jsonRoadMaintenanceParser j(json);
        int final = j.getTaskAmountPerDay();
        //xaxis.push_back(current.toString().toStdString()); jos haluaa timestampit graafiin
        xaxis.push_back(i);
        yaxis.push_back(final);
    }

    updateChart(xaxis, yaxis);
}

void model::getRoadMaintenance(const QDateTime start, const QDateTime end, const  QString taskName, const QString location)
{
    start_ = start;
    end_ = end;

    vector<int> xaxis = {};
    vector<int> yaxis = {};
    int days = start.daysTo(end);

    for (int i = 0; i <= days; i++)
    {
        QDateTime current = start.addDays(i);
        QString dateString = current.date().toString(Qt::ISODate);
        QUrl url = urlBuilder.getRoadMaintenanceUrl(taskName, locations.value(location), dateString);
        QString json = networker_->getUrl(url);
        jsonRoadMaintenanceParser j(json);
        int final = j.getTaskAmountPerDay();
        //xaxis.push_back(current.toString().toStdString()); jos haluaa timestampit graafiin
        xaxis.push_back(i);
        yaxis.push_back(final);
    }
    updateChart(xaxis, yaxis);
}

void model::getRoadCondition(const std::string item, const std::string forecastTime, QString location)
{
    QUrl url = urlBuilder.getRoadConditionUrl(locations.value(location));
    QString json = networker_->getUrl(url);
    jsonRoadConditionParser j(json, item, forecastTime);
    std::string value = j.getWantedValue();
    // TODO display the value
}

void model::getTrafficMsg()
{
    vector<int> xaxis = {};
    vector<int> yaxis = {};
    QUrl url = urlBuilder.getTrafficMsgUrl();
    QString json = networker_->getUrl(url);
    jsonTrafficMessageParser j(json);
    int value = j.getTotalTrafficAmount();
    xaxis.push_back(value);
    // what to add to y axis
    updateChart(xaxis, yaxis);
}

void model::getXmlWeatherObservation(const QString time, const QString param, const QString location)
{
    QUrl url = urlBuilder.getWeatherObservations(time, locations.value(location), param);
    QString xml = networker_->getUrl(url);
    xmlParser xmlPar(xml, param);
    getXmlDataHelper(xml, param);
}

void model::getXmlAvgMinMaxTemp(const QDateTime start, const QDateTime end, const QString param, const QString location)
{
    QString startDate = start.date().toString(Qt::ISODate);
    QString endDate = end.date().toString(Qt::ISODate);
    QUrl url = urlBuilder.getAveragegObservations(startDate, endDate, locations.value(location), param);
    QString xml = networker_->getUrl(url);
    getXmlDataHelper(xml, param);
}

void model::getXmlWeatherForecast(const QDateTime startTime, const QString param, const QString location)
{
    QString startDate = startTime.date().toString(Qt::ISODate);
    QUrl url = urlBuilder.getWeatherForecast(startDate, locations.value(location), param);
    QString xml = networker_->getUrl(url);
    xmlParser xmlPar(xml, param);
    getXmlDataHelper(xml, param);

}

void model::getXmlDataHelper(const QString xml, const QString param)
{
    vector<double> xaxis = {};
    vector<double> yaxis = {};
    xmlParser xmlPar(xml, param);
    std::vector<std::string> data = xmlPar.getValues();
    std::vector<std::string> dateTime = xmlPar.getTimes();
    // WHAT TO DO WITH NAN VALUES AND WHAT TO DO WITH DATES
    for (auto value : data)
    {
        if (value != "NaN") {
            yaxis.push_back(std::stod(value));

        } else {
            yaxis.push_back(0);
        }
    }
    // updateChart(xaxis, yaxis);
}


