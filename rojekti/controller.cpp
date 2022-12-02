#include "controller.h"
#include "QObject"
#include "qlayout.h"
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
void controller::updateGraph(int i, string endDate) {
    //Tells the view to draw a new chart based on inputs
    if(endDate == ""){
        endDate = view_->getTimeRange().second.toString().toStdString();
    }
    QChartView* tempchartview;
    QList<QPointF> pointdata;
    if(i){tempchartview = view_->chartview; pointdata = model_->getChart();}
    else {tempchartview = view_->chartview2; pointdata = model_->pointdata2_;}
    CreateGraph *graph = new CreateGraph();
    QLineSeries* series = new QLineSeries();
    for (auto& point : pointdata) {
            series->append(point);
        }

    graph->drawGraph(series, tempchartview, view_->graphtype, endDate, typeoftime);
    delete graph;
}

//Changes the model to match the selected inputs and then calls updateGraph
void controller::GraphButtonClicked()
{
    QBoxLayout* layout = new QBoxLayout(QBoxLayout::RightToLeft);
    QLabel* displayLabel = new QLabel();
    QFont font = displayLabel->font();
    font.setPointSize(20);
    displayLabel->setFont(font);
    layout->addWidget(displayLabel);
    layout->setAlignment(Qt::AlignHCenter);
    layout->setObjectName("layoutwithlabel");
    typeoftime = "days";
    string endDate = view_->getTimeRange().first.toString().toStdString();

    std::pair<QDateTime, QDateTime> timeRange = view_->getTimeRange();
    //model_->jsonGetData("maintenance","sijainti1");
    std::string location = view_->getLocation();
    MainWindow::Button selected = view_->getCurrentButton();
    if(selected == MainWindow::Button::RoadMaintenance) {
        std::string taskName = view_->getCurrentTask();
        model_->getRoadMaintenance(timeRange.first, timeRange.second, QString::fromStdString(taskName), QString::fromStdString(location));
    } else if (selected == MainWindow::Button::Precipitation || selected == MainWindow::Button::OverallRoadCondition) {
        std::string selectedName;
        std::string forecast = view_->getForecast().toStdString();
        if (selected == MainWindow::Button::Precipitation) {
            selectedName = "precipitationCondition";
        } else if (selected == MainWindow::Button::OverallRoadCondition) {
            selectedName = "overallRoadCondition";

        }

        view_->chartview->setLayout(layout);
        std::string tempstring = model_->getRoadCondition(selectedName, forecast, QString::fromStdString(location));
        displayLabel->setText(QString::fromStdString(tempstring));
        displayLabel->setObjectName(displayLabel->text());

        return;
    } else if (selected == MainWindow::Button::TrafficMessages) {
        view_->chartview->setLayout(layout);
        std::string messageType = view_->getCurrentMessage();
        displayLabel->setText(QString::fromStdString(model_->getTrafficMsg(messageType)));
        displayLabel->setObjectName(displayLabel->text());
        return;
    } else if (selected == MainWindow::Button::TemperatureHistory || selected == MainWindow::Button::ObservedWind || selected == MainWindow::Button::ObservedCloudiness) {
        QString selectedName;
        typeoftime = "hours";
        endDate = view_->getTimeRange().second.toString().toStdString();

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
        typeoftime = "hours2";
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
        endDate = view_->getTimeRange().second.toString().toStdString();
        typeoftime = "hours2";
        // TODO
        if (selected == MainWindow::Button::TemperatureForecast) {
            selectedName = "temperature";
        } else if (selected == MainWindow::Button::PredictedWind) {
            selectedName = "windspeedms";
        }
        // model_->getXmlWeatherForecast(timeRange.first, timeRange.second, selectedName, QString::fromStdString(location));
        model_->getXmlWeatherForecast(timeRange.second, selectedName, QString::fromStdString(location));
    }

    updateGraph(1, endDate);
}

//Saving to file called graphs.txt (initializing if there is none)
void controller::saveButtonClicked(int i) {
    if(i==0 && !view_->chartview->findChild<QBoxLayout*>("layoutwithlabel")){
   QJsonObject savedGraphs = creator_->getGraphsfromfile();
   QJsonObject myObject;
   myObject.insert("type", "normal");
   myObject.insert("typeoftime", QString::fromStdString(typeoftime));
   myObject.insert("endDate", view_->getTimeRange().second.toString());
    QList<QPointF> temp = model_->getChart();
    QMap<QString, QVariant> myMap;
    for (int i = 0; i< temp.size(); i++)
        {
        //x-coordinate saved as a key to call for y coordinate
            myMap.insert(QString::number(temp[i].x()), temp[i].y());
        };
    QJsonValue graphpoints = QJsonValue::fromVariant(myMap);
    myObject.insert("points", graphpoints);
    savedGraphs.insert(view_->placeholdername, myObject);
    creator_->writetoFiles(savedGraphs);
    }
    else if (i  == 0){
       QJsonObject savedGraphs = creator_->getGraphsfromfile();
       QJsonObject myObject;
       myObject.insert("type", "label");
       myObject.insert("endDate", view_->getTimeRange().second.toString());
        myObject.insert("points", view_->chartview->findChild<QLabel*>()->objectName());
        savedGraphs.insert(view_->placeholdername, myObject);
        creator_->writetoFiles(savedGraphs);
    }
    else {
        stringstream t;
        t << "graphImages/" << view_->placeholdername.toStdString() << ".png";
        view_->chartview->grab().save(QString::fromStdString(t.str()));

    }
}

//Draws the chart selected from the dropdown to the compare section
void controller::compareDropdownActivated() {
    if(view_->placeholdername == "Current") {GraphButtonClicked(); model_->pointdata2_ = model_->getChart(); updateGraph(0); return;}
    std::vector<double> xaxis;
    std::vector<double> yaxis;
    QString graphname = view_->placeholdername;
   QJsonObject myObject = creator_->getGraphsfromfile()[graphname].toObject();
   if(myObject["type"].toString() == "normal") {
   QList<QPointF> pointdata;
   for(QString num : myObject["points"].toObject().keys()){pointdata.append(QPointF(num.toDouble(), myObject["points"][num].toDouble()));}
    model_->pointdata2_ = pointdata;
    typeoftime = myObject["typeoftime"].toString().toStdString();
    updateGraph(0, myObject["startDate"].toString().toStdString());}
    else {
       QBoxLayout* layout = new QBoxLayout(QBoxLayout::RightToLeft);
       QLabel* displayLabel = new QLabel();
       QFont font = displayLabel->font();
       layout->addWidget(displayLabel);
       font.setPointSize(20);
       displayLabel->setFont(font);
       layout->setAlignment(Qt::AlignHCenter);
       view_->chartview2->setLayout(layout);
       QString tempstring = myObject["points"].toString();
       displayLabel->setText(tempstring);
    }
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
void controller::PreferenceButtonClicked(int roaddropdownindex, int grapdropdownindex, int roadmaintenancetypeindex, int forecastdropdownindex, int messagetypedropdownindex) {
    QJsonObject Writetofile = creator_->getGraphsfromfile(1);;
    QJsonObject preferences;
    preferences.insert("location", roaddropdownindex);
    preferences.insert("graphtype", grapdropdownindex);
    preferences.insert("radiobutton", view_->preferenceButton_);
    preferences.insert("type_pick", roadmaintenancetypeindex);
    preferences.insert("fhours", forecastdropdownindex);
    preferences.insert("messagetype", messagetypedropdownindex);
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
