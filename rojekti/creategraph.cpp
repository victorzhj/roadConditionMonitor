// Used to create a line chart
#include <QtCharts/QLineSeries>

// Used to change names on axis
#include <QtCharts/QValueAxis>

// Widget used to display charts
#include <QtCharts/QChartView>
#include <QBarSeries>
#include <QBarSet>
#include <iostream>
using namespace std;

class CreateGraph {
private:
public:
void drawGraph(QLineSeries* series, QChartView* object)
{
        // Create chart, add data, hide legend, and add axis
        QChart *chart = new QChart();
        chart->legend()->hide();
        chart->addSeries(series);
        chart->createDefaultAxes();

        object->setChart(chart);

};
void drawBarGraph(QBarSeries* yaxis, QChartView* object)
{
        // Create chart, add data, hide legend, and add axis
        QChart *chart = new QChart();
        chart->legend()->hide();
        chart->addSeries(yaxis);
        chart->createDefaultAxes();}

};
