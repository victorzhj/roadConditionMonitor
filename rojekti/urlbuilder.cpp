#include "urlbuilder.h"

urlBuilder::urlBuilder()
{

}

QUrl urlBuilder::getRoadMaintenanceUrl(QString taskName, QVector<QString> coords, QString date)
{
      QString url = digitrafficBase + "v1/tracking/routes?endFrom="
                + date + "T09%3A00%3A00Z&endBefore=" + date
                + "T14%3A00%3A00Z&xMin=" + coords[0]
                + "&yMin=" + coords[1]
                + "&xMax=" + coords[2]
                + "&yMax=" + coords[3]
                + "&taskId=" + taskName
                + "&domain=state-roads";
      return QUrl(url);
}

QUrl urlBuilder::getRoadConditionUrl(QVector<QString> coords)
{
    QString url = digitrafficBase + "v3/data/road-conditions/"
                + coords[0] + "/" + coords[1]
                + "/" + coords[2] + "/" + coords[3];
    return QUrl(url);
}

QUrl urlBuilder::getTrafficMsgUrl()
{
    QString url = digitrafficBase + "traffic-message/v1/messages?inactiveHours=0&includeAreaGeometry=false&situationType=TRAFFIC_ANNOUNCEMENT";
    return QUrl(url);
}

QUrl urlBuilder::getWeatherObservations(QString time, QVector<QString> coords, QString param)
{
    QString url = fmiBase + "observations::weather::simple&bbox="
            + coords[0] + ","  + coords[1]
            + "," + coords[2] + "," + coords[3]
            +"&timestep=30&parameters=" + param;
    return QUrl(url);
}

QUrl urlBuilder::getAveragegObservations(QString startDate, QString endDate, QString time, QVector<QString> coords, QString param)
{
    QString url = fmiBase + "observations::weather::hourly::simple&bbox="
            + coords[0] + ","  + coords[1]
            + "," + coords[2] + "," + coords[3]
            + "&starttime=" + startDate
            + "T00:00:00Z&endtime=" + endDate
            + "T" + time + "Z"
            + "&parameters=" + param;
    return QUrl(url);
}

QUrl urlBuilder::getWeatherForecast(QString date, QString time, QVector<QString> coords)
{
    QString url = fmiBase
            + "forecast::harmonie::surface::point::simple&latlon="
            + coords[0] + ","  + coords[1]
            + "&timestep=30&starttime="
            + date + "T" + time + "Z"
            + "&endtime=" + date + "T" // päivään pitää lisätä yksi, miten?
            + time + "Z"
            + "&parameters=temperature,windspeedms";
    return QUrl(url);
}
