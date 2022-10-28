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


class model
{
public:
    model();
    QList<QPoint> getChart();
    int getPreferences();
    void updateChart(std::vector<int> timeData, std::vector<int> OtherData);
    void updatePreferences();
private:
    QList<QPoint> pointdata_ = {{1,2}, {2,4}, {3,10}, {4,2}, {5,1}};
    //using int as placeholder type since not sure what it will be
    int preferences_;
};

#endif // MODEL_H
