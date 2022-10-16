#ifndef CREATEGRAPH_H
#define CREATEGRAPH_H

#include <vector>
// Widget used to display charts
#include <QtCharts/QChartView>

class CreateGraph
{
private: QChartView grapher;
public:
    CreateGraph();
    CreateGraph(std::vector<int>, std::vector<int>);

    QChartView returnGraph();
};

#endif // CREATEGRAPH_H
