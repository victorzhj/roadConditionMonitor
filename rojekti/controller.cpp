#include "controller.h"
#include "QObject"

controller::controller(model* model, MainWindow* view, QObject *parent) : QObject(parent)
  , model_(model)
  , view_(view)
{

    QObject::connect(view_, &MainWindow::pushButtonClicked,
                             this, &controller::GraphButtonClicked);
}

void controller::updateGraph() {
    view_->drawGraph(model_);
}

void controller::GraphButtonClicked()
{
    model_->jsonGetData();
    updateGraph();
}
