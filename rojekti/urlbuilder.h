#ifndef URLBUILDER_H
#define URLBUILDER_H

#include <QString>
#include <QUrl>



class urlBuilder
{
public:
    urlBuilder();
    QUrl getRoadMaintenanceUrl(QString whatData, QVector<QString> coords, QString date);
    QUrl getRoadConditionUrl(QVector<QString> coords);
    QUrl getTrafficMsgUrl();
    QUrl getWeatherObservations(QString time, QVector<QString> coords, QString param);
    QUrl getAveragegObservations(QString startDate, QString endDate, QString time, QVector<QString> coords, QString param);
    QUrl getWeatherForecast(QString date, QString time, QVector<QString> coords);

private:
    QString digitrafficBase = "https://tie.digitraffic.fi/api/";
    QString fmiBase = "https://opendata.fmi.fi/wfs?request=getFeature&version=2.0.0&storedquery_id=fmi::";
};

#endif // URLBUILDER_H
