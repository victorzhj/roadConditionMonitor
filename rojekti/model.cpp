#include "model.h"
#include "creategraph.cpp"
#include "jsonroadmaintenanceparser.h"

model::model()
{
}

QList<QPoint> model::getChart() {
    return pointdata_;
}

int model::getPreferences()
{
    return preferences_;
}
//update this when the data is pulled from the networker or loaded from file
void model::updateChart(vector<int> timeData, vector<int> OtherData) {
    for (int i = 0; i < std::min(timeData.size(), OtherData.size()); ++i)
        {
            pointdata_.append(QPoint(timeData[i], OtherData[i]));
        }
}

void model::updatePreferences()
{

}

void model::jsonGetData()
{
    QString json = networker_->getDefault();
    jsonRoadMaintenanceParser j(json);
    qDebug() << j.getTaskAmountPerDay();
}
