// Used to create a line chart
#include <QtCharts/QLineSeries>

// Used to change names on axis
#include <QtCharts/QValueAxis>

// Widget used to display charts
#include <QtCharts/QChartView>
#include <QBarSeries>
#include <QBarSet>
#include <QBarCategoryAxis>
#include <QScatterSeries>
using namespace std;

class CreateGraph {
private:
public:
void drawGraph(QLineSeries* series, QChartView* object, string graphtype)
{
    QVector<QPointF> points = series->points();
    std::sort(points.begin(), points.end(), [](const QPointF & p1, const QPointF & p2) {
        return p1.x() < p2.x();
    });
    QChart *chart = new QChart();
    chart->legend()->hide();
    if(graphtype == "line"){
    series->replace(points);
        chart->addSeries(series);
        chart->createDefaultAxes();
        }
    else if (graphtype == "bar"){
    QBarSet *set = new QBarSet("");

    QBarCategoryAxis *xaxis = new QBarCategoryAxis();
    QValueAxis *yaxis = new QValueAxis();
    int biggesty = 0;
    for(int i = 0; i <points.size(); i++){
        set->append(points[i].y());
        xaxis->append(QString::fromStdString(std::to_string((int)points[i].x())));
        if(points[i].y() > biggesty) {biggesty = points[i].y();};
    }
    yaxis->setRange(0, biggesty);
    QBarSeries *barseries = new QBarSeries();
    barseries->append(set);
    chart->addAxis(xaxis, Qt::AlignBottom);
    chart->addAxis(yaxis, Qt::AlignLeft);
    chart->addSeries(barseries);
    }
    else if (graphtype == "scatter"){
    QScatterSeries *scatters =new QScatterSeries;
    for(int i = 0; i <points.size(); i++){
        scatters->append(points[i].x(), points[i].y());
    }
    chart->addSeries(scatters);
    chart->createDefaultAxes();
    }


        object->setChart(chart);

};

};
