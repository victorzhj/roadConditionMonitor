// Used to create a line chart
#include <QtCharts/QLineSeries>

// Used to change names on axis
#include <QtCharts/QValueAxis>

// Widget used to display charts
#include <QtCharts/QChartView>
#include <QBarSeries>
#include <QBarSet>
using namespace std;

class CreateGraph {
private:
public:
void drawGraph(QLineSeries* series, QFrame* object)
{
        // Create chart, add data, hide legend, and add axis
        QChart *chart = new QChart();
        chart->legend()->hide();
        chart->addSeries(series);
        chart->createDefaultAxes();


        QChartView *graph = new QChartView(chart);
        graph->resize(object->width(),object->height());
        graph->setParent(object);

};
};
