#ifndef URLBUILDER_H
#define URLBUILDER_H

#include <QString>
#include <QUrl>



class urlBuilder
{
public:
    urlBuilder();
    /**
     * @brief urlBuilder::getRoadMaintenanceUrl builds URL to get road maintenance from digitraffic API
     * @param taskName what road maintenance task is wanted. If empty, get all
     * @param coords contains min and max coordinates from within the data is being collected
     * @param date from what day the data is wanted
     * @return finished URL
     */
    QUrl getRoadMaintenanceUrl(QString whatData, QVector<QString> coords, QString date);
    /**
     * @brief urlBuilder::getRoadConditionUrl build URL to get road conditions from digitraffic API
     * @param coords contains min and max coordinates from within the data is being collected
     * @return finished URL
     */
    QUrl getRoadConditionUrl(QVector<QString> coords);
    /**
     * @brief urlBuilder::getTrafficMsgUrl builds URL to get traffic messages from digitraffic API
     * @return finished URL
     */
    QUrl getTrafficMsgUrl(QString messageType);
    /**
     * @brief urlBuilder::getWeatherObservations builds URL to get road maintenance from digitraffic API
     * @param coords contains min and max coordinates from within the data is being collected
     * @param param choose what information is wanted
     * @return finished URL
     */
    QUrl getWeatherObservations(QVector<QString> coords, QString param);
    /**
     * @brief urlBuilder::getAveragegObservations builds URL to get hourly road maintenance from FMI API
     * @param startDate from what day the query starts
     * @param endDate to what day the query ends
     * @param coords contains min and max coordinates from within the data is being collected
     * @param param choose what information is wanted, for example average air temp is "t2m"
     * @return finished URL
     */
    QUrl getAveragegObservations(QString startDate, QString endDate, QVector<QString> coords, QString param);
    /**
     * @brief urlBuilder::getWeatherForecast builds URL to get hourly weather forecast from FMI API
     * @param date from what day the data is wanted
     * @param coords contains min and max coordinates from within the data is being collected
     * @param param choose what information is wanted
     * @return finished URL
     */
    QUrl getWeatherForecast(QString date, QVector<QString> coords, QString param);

private:
    QString digitrafficBase = "https://tie.digitraffic.fi/api/";
    QString fmiBase = "https://opendata.fmi.fi/wfs?request=getFeature&version=2.0.0&storedquery_id=fmi::";
};

#endif // URLBUILDER_H
