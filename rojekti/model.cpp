#include "model.h"
#include "creategraph.cpp"
//these will be replaced with numbers from the API
vector<int> xaxis = {1,2,3,4,5,6,7,8,9};
vector<int> yaxis = {10,20,30,40,50,60,70,80,90};
map<int,int> messages = {{1,2},{2,6},{3,7},{0,10}};

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
