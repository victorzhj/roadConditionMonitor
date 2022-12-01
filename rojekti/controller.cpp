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
    QObject::connect(view_, &MainWindow::graphButtonClicked,
                             this, &controller::GraphButtonClicked);
    QObject::connect(view_, &MainWindow::saveButtonClicked,
                             this, &controller::saveButtonClicked);
    QObject::connect(view_, &MainWindow::compareDropdownActivated,
                             this, &controller::compareDropdownActivated);
    QObject::connect(view_, &MainWindow::deleteButtonClicked,
                             this, &controller::deleteButtonClicked);
    QObject::connect(view_, &MainWindow::PreferenceButtonClicked,
                             this, &controller::PreferenceButtonClicked);
    QObject::connect(view_, &MainWindow::deletePreferenceButtonClicked,
                             this, &controller::deletePreferenceButtonClicked);


}

//Graphs a chart based on the model
void controller::updateGraph(int i) {
    //Tells the view to draw a new chart based on inputs
    QChartView* tempchartview;
    QList<QPointF> pointdata;
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

//Changes the model to match the selected inputs and then calls updateGraph
void controller::GraphButtonClicked()
{
    std::pair<QDateTime, QDateTime> timeRange = view_->getTimeRange();
    //model_->jsonGetData("maintenance","sijainti1");

    std::string location = view_->getLocation();
    MainWindow::Button selected = view_->getCurrentButton();
    if(selected == MainWindow::Button::RoadMaintenance) {
        std::string taskName = view_->getCurrentTask();
        model_->getRoadMaintenance(timeRange.first, timeRange.second, QString::fromStdString(taskName), QString::fromStdString(location));
    } else if (selected == MainWindow::Button::Precipitation || selected == MainWindow::Button::OverallRoadCondition) {
        std::string selectedName;
        if (selected == MainWindow::Button::Precipitation) {
            selectedName = "precipitation";
        } else if (selected == MainWindow::Button::OverallRoadCondition) {
            selectedName = "over all road condition";
        }
        std::string forecast = view_->getForecast().toStdString();
        model_->getRoadCondition(selectedName, forecast, QString::fromStdString(location));
    } else if (selected == MainWindow::Button::TrafficMessages) {
        std::string messageType = view_->getCurrentMessage();
        model_->getTrafficMsg(messageType);
    } else if (selected == MainWindow::Button::TemperatureHistory || selected == MainWindow::Button::ObservedWind || selected == MainWindow::Button::ObservedCloudiness) {
        QString selectedName;

        // TODO
        if (selected == MainWindow::Button::TemperatureHistory) {
            selectedName = "t2m";
        } else if (selected == MainWindow::Button::ObservedWind) {
            selectedName = "ws_10min";
        } else if (selected == MainWindow::Button::ObservedCloudiness) {
            selectedName = "n_man";
        }
        model_->getXmlWeatherObservation(selectedName, QString::fromStdString(location));
    } else if (selected == MainWindow::Button::AverageTemperature || selected == MainWindow::Button::MinimumTemperature || selected == MainWindow::Button::MaximumTemperature) {
        QString selectedName;

        // TODO
        if (selected == MainWindow::Button::AverageTemperature) {
            selectedName = "TA_PT1H_AVG";
        } else if (selected == MainWindow::Button::MinimumTemperature) {
            selectedName = "TA_PT1H_MIN";
        } else if (selected == MainWindow::Button::MaximumTemperature) {
            selectedName = "TA_PT1H_MAX";
        }
        model_->getXmlAvgMinMaxTemp(timeRange.first, timeRange.second, selectedName, QString::fromStdString(location));
    } else if (selected == MainWindow::Button::TemperatureForecast || selected == MainWindow::Button::PredictedWind) {
        QString selectedName;

        // TODO
        if (selected == MainWindow::Button::TemperatureForecast) {
            selectedName = "temperature";
        } else if (selected == MainWindow::Button::PredictedWind) {
            selectedName = "windspeedms";
        }
        // model_->getXmlWeatherForecast(timeRange.first, timeRange.second, selectedName, QString::fromStdString(location));
        model_->getXmlWeatherForecast(timeRange.first, selectedName, QString::fromStdString(location));
    }


    updateGraph(1);
}

//Saving to file called graphs.txt (initializing if there is none)
void controller::saveButtonClicked(int i) {

    if(i==0){
   QJsonObject myObject = creator_->getGraphsfromfile();
    QList<QPointF> temp = model_->getChart();
    QMap<QString, QVariant> myMap;
    for (int i = 0; i< temp.size(); i++)
        {
        //x-coordinate saved as a key to call for y coordinate
            myMap.insert(QString::number(temp[i].x()), temp[i].y());
        };
    QJsonValue myValue = QJsonValue::fromVariant(myMap);
    myObject.insert(view_->placeholdername, myValue);
    creator_->writetoFiles(myObject);
    }
    else {
        stringstream t;
        t << "graphImages/" << view_->placeholdername.toStdString() << ".png";
        view_->chartview->grab().save(QString::fromStdString(t.str()));

    }
}

//Draws the chart selected from the dropdown to the compare section
void controller::compareDropdownActivated() {
    if(view_->placeholdername == "Current") {model_->pointdata2_ = model_->getChart();}
    else{
    std::vector<double> xaxis;
    std::vector<double> yaxis;
    QString graphname = view_->placeholdername;
   QJsonObject myObject = creator_->getGraphsfromfile();
   QList<QPointF> pointdata;
   for(QString num : myObject[graphname].toObject().keys()){
   pointdata.append(QPointF(num.toDouble(), myObject[graphname][num].toDouble()));
   }
    model_->pointdata2_ = pointdata;}
    updateGraph(0);
}

//Deletes the current compare graph
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
   creator_->writetoFiles(myObject);}
   view_->loadCompareItems();
   view_->on_CompareDropdown_activated(0);
}

//Adds the current search to the preferences file
void controller::PreferenceButtonClicked(int i, int j, int h, int k) {
    QJsonObject Writetofile = creator_->getGraphsfromfile(1);;
    QJsonObject preferences;
    QJsonObject dates;
    dates.insert("startdate", view_->getTimeRange().first.toString());
    dates.insert("enddate", view_->getTimeRange().second.toString());
    preferences.insert("location", i);
    preferences.insert("graphtype", j);
    preferences.insert("radiobutton", view_->preferenceButton_);
    preferences.insert("type_pick", h);
    preferences.insert("fhours", k);
    preferences.insert("dates", dates);
    Writetofile.insert(view_->preferenceName, preferences);
    creator_->writetoFiles(Writetofile, 1);
    view_->loadPreferences();

}

//Deletes the saved preference, does nothing if there is no matching name saved (ex. "")
void controller::deletePreferenceButtonClicked() {
   QJsonObject myObject = creator_->getGraphsfromfile(1);
   myObject.remove(view_->preferenceName);
   creator_->writetoFiles(myObject, 1);
   view_->loadPreferences();
}
