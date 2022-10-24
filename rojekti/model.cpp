#include "model.h"
#include "creategraph.cpp"

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
    pointdata_.clear();
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
    jsonNetworker networker;
    networker.get("https://tie.digitraffic.fi/api/v3/data/road-conditions/21.7/61.45/21.8/61.50");
    //cout << s.toStdString() << std::endl;
}
