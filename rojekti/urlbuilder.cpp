#include "urlbuilder.h"

urlBuilder::urlBuilder()
{

}
/**
 * @brief urlBuilder::getRoadMaintenanceUrl builds URL to get road maintenance from digitraffic API
 * @param taskName what road maintenance task is wanted. If empty, get all
 * @param coords contains min and max coordinates from within the data is being collected
 * @param date from what day the data is wanted
 * @return finished URL
 */
QUrl urlBuilder::getRoadMaintenanceUrl(QString taskName, QVector<QString> coords, QString date)
{
      QString url = digitrafficBase + "maintenance/v1/tracking/routes?endFrom="
                + date + "T09%3A00%3A00Z&endBefore=" + date
                + "T14%3A00%3A00Z&xMin=" + coords[0]
                + "&yMin=" + coords[1]
                + "&xMax=" + coords[2]
                + "&yMax=" + coords[3]
                + "&domain=state-roads";
      if (taskName != "") url = url + "&taskId=" + taskName;
      return QUrl(url);
}
/**
 * @brief urlBuilder::getRoadConditionUrl build URL to get road conditions from digitraffic API
 * @param coords contains min and max coordinates from within the data is being collected
 * @return finished URL
 */
QUrl urlBuilder::getRoadConditionUrl(QVector<QString> coords)
{
    QString url = digitrafficBase + "v3/data/road-conditions/"
                + coords[0] + "/" + coords[1]
                + "/" + coords[2] + "/" + coords[3];
    return QUrl(url);
}
/**
 * @brief urlBuilder::getTrafficMsgUrl builds URL to get traffic messages from digitraffic API
 * @return finished URL
 */
QUrl urlBuilder::getTrafficMsgUrl()
{
    QString url = digitrafficBase + "traffic-message/v1/messages?inactiveHours=0&includeAreaGeometry=false&situationType=TRAFFIC_ANNOUNCEMENT";
    return QUrl(url);
}
/**
 * @brief urlBuilder::getWeatherObservations builds URL to get road maintenance from digitraffic API
 * @param coords contains min and max coordinates from within the data is being collected
 * @param param choose what information is wanted
 * @return finished URL
 */
QUrl urlBuilder::getWeatherObservations(QVector<QString> coords, QString param)
{
    QString url = fmiBase + "observations::weather::simple&bbox="
            + coords[0] + ","  + coords[1]
            + "," + coords[2] + "," + coords[3]
            +"&timestep=60&parameters=" + param;
    return QUrl(url);
}
/**
 * @brief urlBuilder::getAveragegObservations builds URL to get hourly road maintenance from FMI API
 * @param startDate from what day the query starts
 * @param endDate to what day the query ends
 * @param coords contains min and max coordinates from within the data is being collected
 * @param param choose what information is wanted, for example average air temp is "t2m"
 * @return finished URL
 */
QUrl urlBuilder::getAveragegObservations(QString startDate, QString endDate, QVector<QString> coords, QString param)
{
    QString url = fmiBase + "observations::weather::hourly::simple&bbox="
            + coords[0] + ","  + coords[1]
            + "," + coords[2] + "," + coords[3]
            + "&starttime=" + startDate
            + "T00:00:00Z&endtime=" + endDate
            + "T23:59:59Z"
            + "&parameters=" + param;
    return QUrl(url);
}
/**
 * @brief urlBuilder::getWeatherForecast builds URL to get hourly weather forecast from FMI API
 * @param date from what day the data is wanted
 * @param coords contains min and max coordinates from within the data is being collected
 * @param param choose what information is wanted
 * @return finished URL
 */
QUrl urlBuilder::getWeatherForecast(QString date, QVector<QString> coords, QString param)
{
    QString url = fmiBase
            + "forecast::harmonie::surface::point::simple&bbox="
            + coords[0] + ","  + coords[1]
            + "," + coords[2] + "," + coords[3]
            + "&timestep=60&starttime="
            + date + "T00:00:00Z"
            + "&endtime=" + date + "T"
            + "23:59:59Z"
            + "&parameters=" + param;
    return QUrl(url);
}
