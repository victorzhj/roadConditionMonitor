#include "controller.h"
#include "QObject"
#include <string>
#include <sstream>
#include <QFile>
#include <QTextStream>
controller::controller(model* model, MainWindow* view, QObject *parent) : QObject(parent)
  , model_(model)
  , view_(view)
{
    creator_ = new fileCreator();
    QObject::connect(view_, &MainWindow::pushButtonClicked,
                             this, &controller::GraphButtonClicked);
    QObject::connect(view_, &MainWindow::saveButtonClicked,
                             this, &controller::saveButtonClicked);
    QObject::connect(view_, &MainWindow::compareDropdownActivated,
                             this, &controller::compareDropdownActivated);
    QObject::connect(view_, &MainWindow::deleteButtonClicked,
                             this, &controller::deleteButtonClicked);

}

void controller::updateGraph(int i) {
    //Tells the view to draw a new chart based on inputs
    QChartView* tempchartview;
    QList<QPoint> pointdata;
    if(i){tempchartview = view_->chartview; pointdata = model_->getChart();}
    else {tempchartview = view_->chartview2; pointdata = model_->pointdata2_;}
    CreateGraph *graph = new CreateGraph();
    QLineSeries* series = new QLineSeries();
    for (auto& point : pointdata) {
            series->append(point);
        }

    graph->drawGraph(series, tempchartview, view_->graphtype);
    delete graph;
}

void controller::GraphButtonClicked()
{
    std::pair<QDateTime, QDateTime> timeRange = view_->getTimeRange();
    model_->setTimeRange(timeRange.first, timeRange.second);
    model_->jsonGetData("maintenance","sijainti1");
    updateGraph(1);
}

//Saving to file called graphs.txt (initializing if there is none)
void controller::saveButtonClicked(int i) {

    if(i==0){
   QJsonObject myObject = creator_->getGraphsfromfile();
    QList<QPoint> temp = model_->getChart();
    QMap<QString, QVariant> myMap;
    for (int i = 0; i< temp.size(); i++)
        {
        //x-coordinate saved as a key to call for y coordinate
            myMap.insert(QString::number(temp[i].x()), temp[i].y());
        };
    QJsonValue myValue = QJsonValue::fromVariant(myMap);
    myObject.insert(view_->placeholdername, myValue);
    creator_->writetoGraphs(myObject);
    }
    else {
        stringstream t;
        t << "graphImages/" << view_->placeholdername.toStdString() << ".png";
        view_->chartview->grab().save(QString::fromStdString(t.str()));

    }
}

void controller::compareDropdownActivated() {
    if(view_->placeholdername == "Current") {model_->pointdata2_ = model_->getChart();}
    else{
    std::vector<int> xaxis;
    std::vector<int> yaxis;
    QString graphname = view_->placeholdername;
   QJsonObject myObject = creator_->getGraphsfromfile();
   QList<QPoint> pointdata;
   for(QString num : myObject[graphname].toObject().keys()){
   pointdata.append(QPoint(num.toInt(), myObject[graphname][num].toInt()));
   }
    model_->pointdata2_ = pointdata;}
    updateGraph(0);
}

void controller::deleteButtonClicked() {
    QList<QString> emptylist = {};
    if(creator_->getImageNames(emptylist).contains(view_->placeholdername)) {
        stringstream s;
        s << "graphImages/" << view_->placeholdername.toStdString() << ".png";
        remove(s.str().c_str());
    }
    else{
   QJsonObject myObject = creator_->getGraphsfromfile();
   myObject.remove(view_->placeholdername);
   creator_->writetoGraphs(myObject);}
   view_->loadCompareItems();
   view_->on_CompareDropdown_activated(0);

   qInfo() << view_->placeholdername;
}
