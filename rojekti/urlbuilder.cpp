#include "urlbuilder.h"

urlBuilder::urlBuilder()
{

}

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

QUrl urlBuilder::getWeatherObservations(QVector<QString> coords, QString param)
{
    QString url = fmiBase + "observations::weather::simple&bbox="
            + coords[0] + ","  + coords[1]
            + "," + coords[2] + "," + coords[3]
            +"&timestep=60&parameters=" + param;
    return QUrl(url);
}

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

QUrl urlBuilder::getWeatherForecast(QString date, QVector<QString> coords, QString param)
{
    QString url = fmiBase
            + "forecast::harmonie::surface::point::simple&latlon="
            + coords[0] + ","  + coords[1]
            + "&timestep=60&starttime="
            + date + "T00:00:00Z"
            + "&endtime=" + date + "T" // päivään pitää lisätä yksi, miten?
            + "23:59:59Z"
            + "&parameters=" + param;
    return QUrl(url);
}
