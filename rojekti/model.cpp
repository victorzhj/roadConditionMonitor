#include "model.h"
#include "creategraph.cpp"
#include "jsonroadmaintenanceparser.h"
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


