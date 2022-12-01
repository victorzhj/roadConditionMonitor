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
#include <QDateTime>
#include <iostream>
using namespace std;

class CreateGraph {
private:
public:

//Draws a graph from the points in series to the object. The type of graph depends on graphtype
void drawGraph(QLineSeries* series, QChartView* object, string graphtype, string startDate, string typeoftime)
{
    QVector<QPointF> points = series->points();
    long double biggesty = 0;
    long double smallesty = 0;
    std::sort(points.begin(), points.end(), [](const QPointF & p1, const QPointF & p2) {
        return p1.x() < p2.x();

    });
    QBarCategoryAxis *xaxis = new QBarCategoryAxis();
    QValueAxis *yaxis = new QValueAxis();
    QDateTime startingdate = QDateTime::fromString(QString::fromStdString(startDate));
    for(int i = 0; i <points.size(); i++){
        if(points[i].y() > biggesty) {biggesty = points[i].y();}
        if(points[i].y() < smallesty) {smallesty = points[i].y();}
        if(typeoftime == "hours") {xaxis->append(QString::fromStdString(std::to_string(startingdate.addSecs(-3600*13 + 3600*i).time().hour())));}
        else if(typeoftime == "hours2") {startingdate.setTime(QTime(startingdate.time().hour() - (points.size()-1), 0));xaxis->append(QString::fromStdString(std::to_string(startingdate.addSecs(3600*i).time().hour())));}
        else if(typeoftime == "days") {xaxis->append(QString::fromStdString(std::to_string(startingdate.addDays(i).date().day())));}
    }

    yaxis->setRange(smallesty*1.1, biggesty*1.3);

    QChart *chart = new QChart();
    chart->addAxis(yaxis, Qt::AlignLeft);
    chart->addAxis(xaxis, Qt::AlignBottom);
    chart->legend()->hide();
    if(graphtype == "line"){
    series->replace(points);
        chart->addSeries(series);
        series->attachAxis(yaxis);
        }
    else if (graphtype == "bar"){
    QBarSet *set = new QBarSet("");

    for(int i = 0; i <points.size(); i++){
        set->append(points[i].y());
    }
    QBarSeries *barseries = new QBarSeries();
    barseries->append(set);
    chart->addSeries(barseries);
    barseries->attachAxis(yaxis);
    }
    else if (graphtype == "scatter"){
    QScatterSeries *scatters =new QScatterSeries;
    for(int i = 0; i <points.size(); i++){
        scatters->append(points[i].x(), points[i].y());
    }
    chart->addSeries(scatters);
    scatters->attachAxis(yaxis);
    }


        object->setChart(chart);

};

};
