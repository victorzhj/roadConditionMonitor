// Used to create a line chart
#include "ui_mainwindow.h"
#include <QtCharts/QLineSeries>

// Used to change names on axis
#include <QtCharts/QValueAxis>

// Widget used to display charts
#include <QtCharts/QChartView>

// Widget used to display charts
#include <QtCharts/QChartView>

using namespace std;

class CreateGraph {
private:
public:
void drawGraph(vector<int> xaxis,vector<int> yaxis, QFrame* object)
{

    //QValueAxis *axisX = new QValueAxis();
    //axisX->setRange(xaxis[0], xaxis[xaxis.size()-1]+1);
    QLineSeries *axisy = new QLineSeries();

        for (int i = 0; i< yaxis.size() ; i++){
            axisy->append(xaxis[i], yaxis[i]);
        }
        // 3. Line chart example
        // Other options here https://doc.qt.io/qt-5.11/qtcharts-customchart-example.html


        // Create chart, add data, hide legend, and add axis
        QChart *chart = new QChart();
        chart->legend()->hide();
        chart->addSeries(axisy);
        chart->createDefaultAxes();


        QChartView *graph = new QChartView(chart);
        graph->resize(object->width(),object->height());
        graph->setParent(object);

};
};
