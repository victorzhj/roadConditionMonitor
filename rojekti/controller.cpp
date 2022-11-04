#include "controller.h"
#include "QObject"
#include "ui_mainwindow.h"
#include <string>
#include <sstream>
#include <QFile>
#include <QTextStream>

controller::controller(model* model, MainWindow* view, QObject *parent) : QObject(parent)
  , model_(model)
  , view_(view)
{

    QObject::connect(view_, &MainWindow::pushButtonClicked,
                             this, &controller::GraphButtonClicked);
    QObject::connect(view_, &MainWindow::saveButtonClicked,
                             this, &controller::saveButtonClicked);
}

void controller::updateGraph() {
    //Tells the view to draw a new chart based on inputs
    view_->drawGraph(model_);
}

void controller::GraphButtonClicked()
{
    std::pair<QDateTime, QDateTime> timeRange = view_->getTimeRange();
    model_->setTimeRange(timeRange.first, timeRange.second);
    model_->jsonGetData();
    updateGraph();
}

void controller::saveButtonClicked() {


    QList<QPoint> temp = model_->getChart();
    QMap<QString, QVariant> myMap;
    for (int i = 0; i< temp.size(); i++)
        {
        //x-coordinate saved as a key to call for y coordinate
            myMap.insert(QString::number(temp[i].x()), temp[i].y());

        };
    QJsonValue myValue = QJsonValue::fromVariant(myMap);
    QJsonObject myObject;
    myObject.insert(view_->placeholdername, myValue);
    QJsonDocument myDoc(myObject);
    //Saving to file called graphs.txt (initializing if there is none)
    QFile file("graphs.txt");
    if(!file.open(QIODevice::Append)){
        qCritical() << file.errorString();
        return;
    }
    file.write(myDoc.toJson());
    file.close();
    view_->addtoCompare();
}
