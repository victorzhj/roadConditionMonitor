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
void drawGraph(QLineSeries* series, QChartView* object)
{
    QVector<QPointF> points = series->points();
    std::sort(points.begin(), points.end(), [](const QPointF & p1, const QPointF & p2) {
        return p1.x() > p2.x();
    });
    series->replace(points);
        // Create chart, add data, hide legend, and add axis
        QChart *chart = new QChart();
        chart->legend()->hide();
        chart->addSeries(series);
        chart->createDefaultAxes();

        object->setChart(chart);

};

};
