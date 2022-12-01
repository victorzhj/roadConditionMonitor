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
}

QList<QPointF> model::getChart() {
    //returns the points on the chart
    return pointdata_;
}

void model::updateChart(vector<double> timeData, vector<double> OtherData) {
    //Combines two vectors into chart points (QPointF)
    pointdata_.clear();
    for (unsigned long int i = 0; i < std::min(timeData.size(), OtherData.size()); ++i)
        {
            pointdata_.append(QPointF(timeData[i], OtherData[i]));
        }
}

void model::getRoadMaintenance(const QDateTime start, const QDateTime end, const  QString taskName, const QString location)
{
    start_ = start;
    end_ = end;

    vector<double> xaxis = {};
    vector<double> yaxis = {};
    int days = start.daysTo(end);

    for (int i = 0; i <= days; i++)
    {
        QDateTime current = start.addDays(i);
        QString dateString = current.date().toString(Qt::ISODate);
        QUrl url = urlBuilder.getRoadMaintenanceUrl(taskName, locations.value(location), dateString);
        QString json = networker_->getData(url);
        jsonRoadMaintenanceParser j(json);
        int final = stoi(j.getValue());
        //xaxis.push_back(current.toString().toStdString()); jos haluaa timestampit graafiin
        xaxis.push_back(i);
        yaxis.push_back(final);
    }
    updateChart(xaxis, yaxis);

}

std::string model::getRoadCondition(const std::string item, const std::string forecastTime, QString location)
{
    QUrl url = urlBuilder.getRoadConditionUrl(locations.value(location));
    QString json = networker_->getData(url);
    jsonRoadConditionParser j(json, item, forecastTime);
    std::string value = j.getValue();
    return value;
}

std::string model::getTrafficMsg(std::string messageType)
{
    QUrl url = urlBuilder.getTrafficMsgUrl(QString::fromStdString(messageType));
    QString json = networker_->getData(url);
    jsonTrafficMessageParser j(json);
    return j.getValue();
}

void model::getXmlWeatherObservation(const QString param, const QString location)
{
    QUrl url = urlBuilder.getWeatherObservations(locations.value(location), param);
    QString xml = networker_->getData(url);
    xmlParser xmlPar(xml, param);
    getXmlDataHelper(xml, param);
}

void model::getXmlAvgMinMaxTemp(const QDateTime start, const QDateTime end, const QString param, const QString location)
{
    QString startDate = start.date().toString(Qt::ISODate);
    QString endDate = end.date().toString(Qt::ISODate);
    QUrl url = urlBuilder.getAveragegObservations(startDate, endDate, locations.value(location), param);
    qInfo() << url.toString();
    QString xml = networker_->getData(url);
    getXmlDataHelper(xml, param);
}

void model::getXmlWeatherForecast(const QDateTime startTime, const QDateTime endTime, const QString param, const QString location)
{
    QString startDate = startTime.date().toString(Qt::ISODate);
    QString endDate = endTime.date().toString(Qt::ISODate);
    QUrl url = urlBuilder.getWeatherForecast(startDate, endDate, locations.value(location), param);
    QString xml = networker_->getData(url);
    qDebug() << url.toString();
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
    for (unsigned long int index = 0; index < data.size(); index++)
    {

        yaxis.push_back(std::stod(data[index]));
        xaxis.push_back(index);
    }
    updateChart(xaxis, yaxis);
}


